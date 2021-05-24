// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Health.h"
#include "Interface/Attack.h"
#include "CharacterBase.generated.h"

UCLASS()
class BDEMO_API ACharacterBase : public ACharacter,public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region IHealth function Override
	virtual void OnReceiveDamage_Implementation(int DamageValue) override;
	virtual void OnReceiveRecover_Implementation(int RecoverValue) override;
	virtual void OnRebirth_Implementation() override;
	virtual void OnDead_Implementation() override;
	virtual void UpdateHp_Implementation() override;
#pragma endregion

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Health)
	int CurrentHp;
	UPROPERTY(BlueprintReadOnly, Category = Health)
	int MaxHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool IsDead;
};
