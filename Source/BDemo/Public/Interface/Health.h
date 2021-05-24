// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Health.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BDEMO_API IHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnReceiveDamage(int DamageValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnReceiveRecover(int RecoverValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRebirth();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateHp();
};
