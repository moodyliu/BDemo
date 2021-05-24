// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ANS_EnableAttack.h"
#include "Character/BDemoPlayer.h"
#include "Character/BDemoBoss.h"
#include "Attackable/WeaponBase.h"

void UANS_EnableAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* Owner = MeshComp->GetOwner();
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(Owner);
	if (Player)
	{
		AWeaponBase* Weapon = Player->CurrentWeapon;
		Weapon->BeginAttackCheck();
	}
	ABDemoBoss* Boss = Cast<ABDemoBoss>(Owner);
	if (Boss)
	{
		AWeaponBase* Weapon = Boss->CurrentWeapon;
		Weapon->BeginAttackCheck();
	}
}

void UANS_EnableAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(Owner);
	if (Player)
	{
		AWeaponBase* Weapon = Player->CurrentWeapon;
		Weapon->EndAttackCheck();
	}
	ABDemoBoss* Boss = Cast<ABDemoBoss>(Owner);
	if (Boss)
	{
		AWeaponBase* Weapon = Boss->CurrentWeapon;
		Weapon->EndAttackCheck();
	}
}
