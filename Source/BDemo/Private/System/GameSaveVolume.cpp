// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameSaveVolume.h"
#include "Character/BDemoPlayer.h"
#include "Components/BoxComponent.h"

AGameSaveVolume::AGameSaveVolume()
{
	PrimaryActorTick.bCanEverTick = true;
	Volume = CreateDefaultSubobject<UBoxComponent>("Volume");
	RootComponent = Volume;
	Volume->OnComponentBeginOverlap.AddDynamic(this, &AGameSaveVolume::OnOverlapBegin);
}

void AGameSaveVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABDemoPlayer* Player = Cast<ABDemoPlayer>(OtherActor);
		if (Player)
		{
			Player->SaveGame();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Game Data Saved!")));
		}
	}
}
