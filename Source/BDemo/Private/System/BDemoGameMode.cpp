// Copyright Epic Games, Inc. All Rights Reserved.

#include "System/BDemoGameMode.h"
#include "Character/BDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABDemoGameMode::ABDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
