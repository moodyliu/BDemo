// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BDemoPlayer.h"
#include "Animation/IKAnimInstance.h"
#include "System/BDemoGameModeBase.h"
#include "UMG/PlayerWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/PlayerDataAsset.h"
#include "System/PlayerSaveGame.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "algorithm"

void ABDemoPlayer::MoveRight(float Val)
{
	AddMovementInput(FVector(0.f, -1.f, 0.f), Val);
}

void ABDemoPlayer::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();
}

void ABDemoPlayer::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ABDemoPlayer::Melee()
{
	if (IsUsingSkill())
	{
		return;
	}
	if (InitDataAsset && !(InitDataAsset->MeleeMontages.Num() == 0))
	{
		TArray<UAnimMontage*>& MeleeMontages = InitDataAsset->MeleeMontages;
		int32 RandomIndex = UKismetMathLibrary::RandomInteger(MeleeMontages.Num());
		UAnimMontage* RandomMontage = MeleeMontages[RandomIndex];
		GetMesh()->GetAnimInstance()->Montage_Play(RandomMontage);
	}
}

void ABDemoPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABDemoPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABDemoPlayer::StopJumping);
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &ABDemoPlayer::Melee);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABDemoPlayer::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABDemoPlayer::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABDemoPlayer::TouchStopped);
}

float ABDemoPlayer::IKFootTrace(FName SocketName, float TraceDistance, FRotator& Rotator)
{
	FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
	FVector ActorLocation = GetActorLocation();
	
	float BeginLocationZ = ActorLocation.Z - CapsuleHalfHeight / 2;
	FVector BeginLocation(SocketLocation.X, SocketLocation.Y, BeginLocationZ);
	float EndLocationZ = ActorLocation.Z - CapsuleHalfHeight - TraceDistance;
	FVector EndLocation(SocketLocation.X, SocketLocation.Y, EndLocationZ);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ EObjectTypeQuery::ObjectTypeQuery1 };
	FHitResult Result;
	bool CanHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), BeginLocation, EndLocation, ObjectTypes, false,TArray<AActor*>() , EDrawDebugTrace::None,Result , true, FLinearColor::Red, FLinearColor::Green, 0.f);

	if (CanHit) 
	{
		FVector Normal = Result.Normal;
		
		Rotator = FRotator(FMath::RadiansToDegrees(-FMath::Atan2(Normal.X, Normal.Z)), 0.f, FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.Z)));
	}

	return CanHit ? (Result.Distance - CapsuleHalfHeight/2 + IKFootOffset) : 0.f;
}

void ABDemoPlayer::IKFootTick(float DeltaTime)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UIKAnimInstance* IKAnimInstance = Cast<UIKAnimInstance>(AnimInstance);
	if (IKAnimInstance == nullptr)
	{
		return;
	}
	FRotator LeftRotator(0.f,0.f,0.f);
	FRotator RightRotator(0.f, 0.f, 0.f);
	float LeftOffest = IKFootTrace(FName("LeftFoot"), FootTraceDistance, LeftRotator);
	float RightOffest = IKFootTrace(FName("RightFoot"), FootTraceDistance, RightRotator);
	IKLeftFootOffset = FMath::FInterpTo(IKLeftFootOffset, LeftOffest, DeltaTime, IKInterpSpeed);
	IKRightFootOffset = FMath::FInterpTo(IKRightFootOffset, RightOffest, DeltaTime, IKInterpSpeed);
	float HipsOffset = std::max(IKLeftFootOffset, IKRightFootOffset);
	//IKAnimInstance->BodyOffset = IKHipsOffset;
	IKHipsOffset = FMath::FInterpTo(IKHipsOffset, HipsOffset, DeltaTime, IKInterpSpeed);
	IKAnimInstance->BodyOffset = IKHipsOffset;

	IKAnimInstance->LeftFootEffector = FVector(0.f, IKLeftFootOffset - IKHipsOffset, 0.f);
	IKAnimInstance->RightFootEffector = FVector(0.f, IKRightFootOffset - IKHipsOffset, 0.f);
	IKAnimInstance->LeftFootRotator = LeftRotator;
	IKAnimInstance->RightFootRotator = RightRotator;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("%f"), IKHipsOffset));
	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeight - IKHipsOffset / 2.f);
}

void ABDemoPlayer::IKHandTick(float DeltaTime)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UIKAnimInstance* IKAnimInstance = Cast<UIKAnimInstance>(AnimInstance);
	if (IKAnimInstance == nullptr)
	{
		return;
	}
	if (CurrentWeapon == nullptr || CurrentWeapon->Mesh == nullptr)
	{
		IKLeftHandAlpha = 0.f;
		return;
	}
	IKLeftHandAlpha = FMath::FInterpTo(IKLeftHandAlpha, TargetHandAlpha, DeltaTime,IKHandInterpSpeed);
	IKAnimInstance->LeftHandAlpha = IKLeftHandAlpha;
	FVector LeftHandSocketLocation = CurrentWeapon->Mesh->GetSocketLocation(FName(TEXT("LeftHandSocket")));
	FVector LeftHandSocketBoneSpaceLocation;
	FRotator TempRotator;
	GetMesh()->TransformToBoneSpace(FName(TEXT("RightHand")), LeftHandSocketLocation, FRotator(), LeftHandSocketBoneSpaceLocation, TempRotator);
	IKAnimInstance->LeftHandTrans = FTransform(LeftHandSocketBoneSpaceLocation);
}

void ABDemoPlayer::LoadData(class UPlayerDataAsset* PlayerDataAsset)
{
	if (PlayerDataAsset) 
	{
		MaxHp = PlayerDataAsset->MaxHp;
		AttachWeapon(PlayerDataAsset->Weapon);
	}
}

// 加载初始化数据
ABDemoPlayer::ABDemoPlayer()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
}

bool ABDemoPlayer::IsUsingSkill()
{
	return GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
}

void ABDemoPlayer::BeginPlay()
{
	Super::BeginPlay();
	ABDemoGameModeBase* GM = GetWorld()->GetAuthGameMode<ABDemoGameModeBase>();
	GM->AddPlayerUI();
	CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	ActorZScale = GetActorTransform().GetScale3D().Z;
	LoadData(InitDataAsset);
	SetHandIKState(true);
	Execute_OnRebirth(this);
	LoadGame();
}

void ABDemoPlayer::EndPlay(EEndPlayReason::Type Reason)
{
	ABDemoGameModeBase* GM = GetWorld()->GetAuthGameMode<ABDemoGameModeBase>();
	GM->RemovePlayerUI();
}

void ABDemoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IKFootTick(DeltaTime);
	IKHandTick(DeltaTime);
}

void ABDemoPlayer::AttachWeapon(TSubclassOf<AWeaponBase> WeaponClass)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}
	CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass,FTransform());
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(
			EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), FName("WeaponSocket"));
		CurrentWeapon->SetInstigator(this);
	}
}

void ABDemoPlayer::SetHandIKState(bool IsEnable)
{
	if (IsEnable)
	{
		TargetHandAlpha = 1.f;
	}
	else
	{
		TargetHandAlpha = 0.f;
	}
}

void ABDemoPlayer::SaveGame()
{
	UPlayerSaveGame* Instance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	Instance->RebirthLocation = GetActorLocation();
	UGameplayStatics::SaveGameToSlot(Instance, TEXT("Player"), 0);
}

// 加载存档数据
void ABDemoPlayer::LoadGame()
{
	UPlayerSaveGame* Instance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player"),0));
	if (Instance == nullptr) return;
	SetActorLocation(Instance->RebirthLocation + RebirthLocationOffset);
}

void ABDemoPlayer::UpdateHp_Implementation()
{
	Super::UpdateHp_Implementation();
	ABDemoGameModeBase* GM = GetWorld()->GetAuthGameMode<ABDemoGameModeBase>();
	UPlayerWidget* UserWidget = Cast<UPlayerWidget>(GM->PlayerWidgetInst);
	UserWidget->SetHPBarPercent(CurrentHp / (float)MaxHp);
}

void ABDemoPlayer::OnDead_Implementation()
{
	Super::OnDead_Implementation();
}

void ABDemoPlayer::OnRebirth_Implementation()
{
	Super::OnRebirth_Implementation();
	//Execute_UpdateHp(this);
}

void ABDemoPlayer::OnReceiveRecover_Implementation(int RecoverValue)
{
	Super::OnReceiveRecover_Implementation(RecoverValue);
}

void ABDemoPlayer::OnReceiveDamage_Implementation(int DamageValue)
{
	Super::OnReceiveDamage_Implementation(DamageValue);
	if (!IsUsingSkill())
	{
		if (InitDataAsset && !(InitDataAsset->ImpactMontages.Num() == 0))
		{
			TArray<UAnimMontage*>& ImpactMontages = InitDataAsset->ImpactMontages;
			int32 RandomIndex = UKismetMathLibrary::RandomInteger(ImpactMontages.Num());
			UAnimMontage* RandomMontage = ImpactMontages[RandomIndex];
			GetMesh()->GetAnimInstance()->Montage_Play(RandomMontage);
		}
	}
}

