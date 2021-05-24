// Fill out your copyright notice in the Description page of Project Settings.


#include "Properties/PropertyBase.h"
#include "Character/BDemoPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APropertyBase::APropertyBase()
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
	OnActorBeginOverlap.AddDynamic(this, &APropertyBase::OnCollision);

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(HandleComponent);
}

// Called when the game starts or when spawned
void APropertyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APropertyBase::OnCollision(AActor* OverlapedActor, AActor* OtherActor)
{
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(OtherActor);
	if (Player)
	{
		ApplyToPlayer(Player);
		if (TipWave)
		{
			UGameplayStatics::PlaySoundAtLocation(this, TipWave, GetActorLocation());
		}
		Destroy();
	}
}

// Called every frame
void APropertyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropertyBase::ApplyToPlayer_Implementation(class ABDemoPlayer* Player)
{

}

