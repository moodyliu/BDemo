// Fill out your copyright notice in the Description page of Project Settings.


#include "Properties/WeaponProperty.h"
#include "Character/BDemoPlayer.h"

void AWeaponProperty::ApplyToPlayer_Implementation(class ABDemoPlayer* Player)
{
	if (Player)
	{
		Player->AttachWeapon(WeaponClass);
	}
}
