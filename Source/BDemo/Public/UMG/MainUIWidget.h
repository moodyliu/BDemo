// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainUIWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void LoadGameLevel();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UPROPERTY(EditAnywhere)
	FName GameLevelName;
protected:
	virtual void NativeConstruct() override;

private:
	class UButton* EndBtn;
	class UButton* BeginBtn;
};
