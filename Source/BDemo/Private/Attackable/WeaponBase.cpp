// Fill out your copyright notice in the Description page of Project Settings.


#include "Attackable/WeaponBase.h"
#include "Character/BDemoPlayer.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandleComponent = CreateDefaultSubobject<UCapsuleComponent>("HandleComponent");
	HandleComponent->InitCapsuleSize(2.f, 2.f);
	HandleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = HandleComponent;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(20.f, 80.f);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CapsuleComponent->SetupAttachment(HandleComponent);
	OnActorBeginOverlap.AddDynamic(this, &AWeaponBase::OnCollision);

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(HandleComponent);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	AActor::BeginPlay();
	EndAttackCheck();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void AWeaponBase::OnAttack_Implementation(TScriptInterface<class IHealth>& Health)
{
	APawn* Inst = GetInstigator();
	if (Inst == nullptr) return;
	//IAttack* Attack = Cast<IAttack>(Inst);
	/*if (Attack == nullptr) return;

	Execute_OnAttack(Attack->_getUObject(), Health);*/
	//Attack->OnAttack(Health);
	IHealth::Execute_OnReceiveDamage(Health->_getUObject(), AttackPower);
}

void AWeaponBase::OnCollision(AActor* OverlapedActor, AActor* OtherActor)
{
	if (CanAttack(OtherActor))
	{
		IHealth* Health = Cast<IHealth>(OtherActor);
		if (Health == nullptr) return;
		TScriptInterface<IHealth> HealthInterface(Health->_getUObject());
		Execute_OnAttack(this, HealthInterface);
	}
}

void AWeaponBase::BeginAttackCheck()
{
	SetActorEnableCollision(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeaponBase::EndAttackCheck()
{
	SetActorEnableCollision(false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AWeaponBase::CanAttack(AActor* OtherActor)
{
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(OtherActor);
	bool IsPlayer = (Player != nullptr);
	bool IsPlayerAttackPlayer = IsPlayer && IsPlayerWeapon;
	bool IsOtherAttackOther = (!IsPlayer) && (!IsPlayerWeapon);
	return (!IsPlayerAttackPlayer) && (!IsOtherAttackOther);
}

