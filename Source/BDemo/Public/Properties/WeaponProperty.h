// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Properties/PropertyBase.h"
#include "Attackable/WeaponBase.h"
#include "WeaponProperty.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API AWeaponProperty : public APropertyBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponClass;

	virtual void ApplyToPlayer_Implementation(class ABDemoPlayer* Player) override;
};
