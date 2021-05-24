// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Properties/PropertyBase.h"
#include "RecoverProperty.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API ARecoverProperty : public APropertyBase
{
	GENERATED_BODY()
	
protected:
	virtual void ApplyToPlayer_Implementation(class ABDemoPlayer* Player) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int RecoverValue;
};
