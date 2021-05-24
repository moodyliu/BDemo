// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "BDemoBoss.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API ABDemoBoss : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Melee();

	void LoadData(class UPlayerDataAsset* PlayerDataAsset);

	ABDemoBoss();

	UFUNCTION(BlueprintCallable)
	bool IsUsingSkill();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<AWeaponBase> WeaponClass);

#pragma region IHealth function Override
	virtual void OnReceiveDamage_Implementation(int DamageValue) override;
	virtual void OnReceiveRecover_Implementation(int RecoverValue) override;
	virtual void OnRebirth_Implementation() override;
	virtual void OnDead_Implementation() override;
	virtual void UpdateHp_Implementation() override;
#pragma endregion

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Attack)
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere)
	class UPlayerDataAsset* InitDataAsset;
};
