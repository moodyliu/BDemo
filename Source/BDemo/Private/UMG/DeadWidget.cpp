// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/DeadWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

UDeadWidget::UDeadWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	BackBtn = nullptr;
	ReplayBtn = nullptr;
}

void UDeadWidget::Replay()
{
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UDeadWidget::BackToMain()
{
	UGameplayStatics::OpenLevel(this, MainLavelName);
}

void UDeadWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UButton* bar = Cast<UButton>(GetWidgetFromName(FName(TEXT("ReplayBtn")))))
	{
		ReplayBtn = bar;
		ReplayBtn->OnClicked.AddDynamic(this, &UDeadWidget::Replay);
	}
	if (UButton* bar = Cast<UButton>(GetWidgetFromName(FName(TEXT("BackBtn")))))
	{
		BackBtn = bar;
		BackBtn->OnClicked.AddDynamic(this, &UDeadWidget::BackToMain);
	}
}

void UDeadWidget::Resume()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetPause(false);
	Controller->bShowMouseCursor = false;
}
