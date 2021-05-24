// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ANS_DisableHandIK.h"
#include "Character/BDemoPlayer.h"

void UANS_DisableHandIK::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* Owner = MeshComp->GetOwner();
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(Owner);
	if (Player)
	{
		Player->SetHandIKState(false);
	}
}

void UANS_DisableHandIK::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();
	ABDemoPlayer* Player = Cast<ABDemoPlayer>(Owner);
	if (Player)
	{
		Player->SetHandIKState(true);
	}
}
