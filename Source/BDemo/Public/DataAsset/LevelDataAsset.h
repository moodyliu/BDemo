// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Enemy)
	TArray<TSubclassOf<AActor>> Enemies;
	UPROPERTY(EditAnywhere, Category = Enemy)
	int32 CreateEnemyCount;
};
