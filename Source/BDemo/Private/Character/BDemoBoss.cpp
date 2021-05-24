// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BDemoBoss.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/PlayerDataAsset.h"
#include "System/PlayerSaveGame.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

void ABDemoBoss::Melee()
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

void ABDemoBoss::LoadData(class UPlayerDataAsset* PlayerDataAsset)
{
	if (PlayerDataAsset)
	{
		MaxHp = PlayerDataAsset->MaxHp;
		AttachWeapon(PlayerDataAsset->Weapon);
	}
}

ABDemoBoss::ABDemoBoss()
{

}

bool ABDemoBoss::IsUsingSkill()
{
	return GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
}

void ABDemoBoss::BeginPlay()
{
	Super::BeginPlay();
	LoadData(InitDataAsset);
	Execute_OnRebirth(this);
}

void ABDemoBoss::AttachWeapon(TSubclassOf<AWeaponBase> WeaponClass)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}
	CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, FTransform());
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(
			EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), FName("WeaponSocket"));
		CurrentWeapon->SetInstigator(this);
	}
}

void ABDemoBoss::UpdateHp_Implementation()
{
	Super::UpdateHp_Implementation();
}

void ABDemoBoss::OnDead_Implementation()
{
	Super::OnDead_Implementation();
}

void ABDemoBoss::OnRebirth_Implementation()
{
	Super::OnRebirth_Implementation();
}

void ABDemoBoss::OnReceiveRecover_Implementation(int RecoverValue)
{
	Super::OnReceiveDamage_Implementation(RecoverValue);
}

void ABDemoBoss::OnReceiveDamage_Implementation(int DamageValue)
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
