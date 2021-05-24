// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void SetHPBarPercent(float Percent);
protected:
	virtual void NativeConstruct() override;

private:
	class UImage* HPBar;
};
