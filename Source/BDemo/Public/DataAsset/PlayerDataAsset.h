// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Attackable/WeaponBase.h"
#include "PlayerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Player)
	int MaxHp;

	UPROPERTY(EditAnywhere, Category = Player)
	TSubclassOf<AWeaponBase> Weapon;

	UPROPERTY(EditAnywhere, Category = Player)
	TArray<UAnimMontage*> MeleeMontages;

	UPROPERTY(EditAnywhere, Category = Player)
	TArray<UAnimMontage*> ImpactMontages;
};
