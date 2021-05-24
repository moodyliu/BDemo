// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attackable/Obstacle.h"
#include "Interface/Health.h"
#include "PingpongObstacle.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API APingpongObstacle : public AObstacle,public IHealth
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* LocationMark1;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* LocationMark2;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly)
	class UEnemyDataAsset* EnemyDataAsset;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly)
	float InterpSpeed;

	USceneComponent* TargetMark;

	virtual void OnReceiveDamage_Implementation(int DamageValue) override;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void MoveToTarget(USceneComponent* Target);

	void SpawnRandomProperty();
public:
	APingpongObstacle();
};
