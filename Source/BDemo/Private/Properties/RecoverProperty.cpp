// Fill out your copyright notice in the Description page of Project Settings.


#include "Properties/RecoverProperty.h"
#include "Character/BDemoPlayer.h"
#include "Interface/Health.h"

void ARecoverProperty::ApplyToPlayer_Implementation(class ABDemoPlayer* Player)
{
	if (Player)
	{
		IHealth::Execute_OnReceiveRecover(Player, RecoverValue);
	}
}
