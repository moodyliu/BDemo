// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSaveVolume.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API AGameSaveVolume : public AActor
{
	GENERATED_BODY()
	

public:
	AGameSaveVolume();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* Volume;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
};
