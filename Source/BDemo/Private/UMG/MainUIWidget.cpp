// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MainUIWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


UMainUIWidget::UMainUIWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	BeginBtn = nullptr;
	EndBtn = nullptr;
}

void UMainUIWidget::LoadGameLevel()
{
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UMainUIWidget::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
	//UKismetSystemLibrary::QuitGame(this,);
}

void UMainUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UButton* bar = Cast<UButton>(GetWidgetFromName(FName(TEXT("BeginBtn")))))
	{
		BeginBtn = bar;
		BeginBtn->OnClicked.AddDynamic(this, &UMainUIWidget::LoadGameLevel);
	}
	if (UButton* bar = Cast<UButton>(GetWidgetFromName(FName(TEXT("EndBtn")))))
	{
		EndBtn = bar;
		EndBtn->OnClicked.AddDynamic(this, &UMainUIWidget::ExitGame);
	}
}
