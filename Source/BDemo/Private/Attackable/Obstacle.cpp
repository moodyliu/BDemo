// Fill out your copyright notice in the Description page of Project Settings.


#include "Attackable/Obstacle.h"
#include "Interface/Health.h"
#include "Character/BDemoPlayer.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandleComponent = CreateDefaultSubobject<UCapsuleComponent>("HandleComponent");
	HandleComponent->InitCapsuleSize(2.f, 2.f);
	HandleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = HandleComponent;

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(HandleComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(20.f, 80.f);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CapsuleComponent->SetupAttachment(Mesh);
	OnActorBeginOverlap.AddDynamic(this, &AObstacle::OnCollision);

	BeginAttackCheck();
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OnCollision(AActor* OverlapedActor, AActor* OtherActor)
{
	if (CanAttack(OtherActor))
	{
		IHealth* Health = Cast<IHealth>(OtherActor);
		if (Health == nullptr) return;
		TScriptInterface<IHealth> HealthInterface(Health->_getUObject());
		Execute_OnAttack(this, HealthInterface);
	}
}

void AObstacle::BeginAttackCheck()
{
	SetActorEnableCollision(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AObstacle::EndAttackCheck()
{
	SetActorEnableCollision(false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AObstacle::CanAttack(AActor* OtherActor)
{
	return Cast<ABDemoPlayer>(OtherActor) != nullptr;
}

void AObstacle::OnAttack_Implementation(TScriptInterface<class IHealth>& Health)
{
	if (Health)
	{
		IHealth::Execute_OnReceiveDamage(Health->_getUObject(), AttackPower);
	}
}

