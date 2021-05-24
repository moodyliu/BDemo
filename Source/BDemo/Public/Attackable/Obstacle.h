// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Attack.h"
#include "Obstacle.generated.h"

UCLASS()
class BDEMO_API AObstacle : public AActor,public IAttack
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int AttackPower;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* HandleComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAttack_Implementation(TScriptInterface<class IHealth>& Health) override;

	UFUNCTION()
	void OnCollision(AActor* OverlapedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void BeginAttackCheck();

	UFUNCTION(BlueprintCallable)
	void EndAttackCheck();

	UFUNCTION(BlueprintCallable)
	bool CanAttack(AActor* OtherActor);

};
