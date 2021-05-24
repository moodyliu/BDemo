// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BDemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API ABDemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABDemoGameModeBase();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* PlayerWidgetInst;

	void AddPlayerUI();

	void RemovePlayerUI();

protected:
	virtual void BeginPlay() override;
};
