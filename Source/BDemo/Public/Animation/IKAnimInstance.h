// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IKAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UIKAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	FVector LeftFootEffector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	FVector RightFootEffector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	float BodyOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	FRotator LeftFootRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	FRotator RightFootRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	FTransform LeftHandTrans;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IKSetting)
	float LeftHandAlpha;
};
