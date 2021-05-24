// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BDemoGameModeBase.h"
#include "Character/BDemoPlayer.h"

ABDemoGameModeBase::ABDemoGameModeBase()
{
	PlayerWidgetInst = nullptr;
}

void ABDemoGameModeBase::AddPlayerUI()
{
	if (PlayerWidgetInst)
	{
		PlayerWidgetInst->RemoveFromViewport();
		PlayerWidgetInst = nullptr;
	}
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (PlayerWidgetClass)
		{
			PlayerWidgetInst = CreateWidget<UUserWidget>(PC, PlayerWidgetClass);
			if (PlayerWidgetInst)
			{
				PlayerWidgetInst->AddToViewport();
			}
		}
	}
	
}

void ABDemoGameModeBase::RemovePlayerUI()
{
	if (PlayerWidgetInst)
	{
		PlayerWidgetInst->RemoveFromViewport();
		PlayerWidgetInst = nullptr;
	}
}

void ABDemoGameModeBase::BeginPlay()
{
	
}
