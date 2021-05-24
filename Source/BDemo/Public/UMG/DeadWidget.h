// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API UDeadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDeadWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void Replay();

	UFUNCTION(BlueprintCallable)
	void BackToMain();

	UPROPERTY(EditAnywhere)
	FName GameLevelName;

	UPROPERTY(EditAnywhere)
	FName MainLavelName;

protected:
	virtual void NativeConstruct() override;

private:
	class UButton* ReplayBtn;
	class UButton* BackBtn;

	void Resume();
};
