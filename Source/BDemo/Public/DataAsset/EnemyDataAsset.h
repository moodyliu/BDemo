// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Properties/PropertyBase.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<APropertyBase>> SpawnProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SpawnChance;
};
