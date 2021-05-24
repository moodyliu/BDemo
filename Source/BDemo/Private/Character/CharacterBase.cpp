// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "algorithm"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHp = 100;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	// Execute_OnRebirth(this);
	// TScriptInterface<IHealth> Health(this);
	// Execute_OnAttack(this,Health);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::UpdateHp_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hp Update:%d"), CurrentHp));
}

void ACharacterBase::OnDead_Implementation()
{
	// UKismetSystemLibrary::PrintString(this,TEXT("OnDead"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnDead")));
	IsDead = true;
}

void ACharacterBase::OnRebirth_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("OnRebirth")));
	CurrentHp = MaxHp;
	IsDead = false;
	Execute_UpdateHp(this);
}

void ACharacterBase::OnReceiveRecover_Implementation(int RecoverValue)
{
	if (RecoverValue < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You should use OnDamage : %d"), RecoverValue));
		return;
	}
	if (IsDead) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Character is dead, you should rebirth it first")));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OnRecover:%d"), RecoverValue));
	CurrentHp = std::min(CurrentHp + RecoverValue, MaxHp);
	Execute_UpdateHp(this);
}

void ACharacterBase::OnReceiveDamage_Implementation(int DamageValue)
{
	if (DamageValue < 0) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You should use OnRecover : %d"), DamageValue));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OnDamage:%d"), DamageValue));
	if (IsDead) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("The Character is Dead!")));
		return;
	}

	// À¿Õˆ≈–∂œ
	CurrentHp = std::max(0, CurrentHp - DamageValue);
	if (CurrentHp == 0) 
	{
		Execute_OnDead(this);
	}
	Execute_UpdateHp(this);
}

