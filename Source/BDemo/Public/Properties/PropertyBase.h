// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropertyBase.generated.h"

UCLASS()
class BDEMO_API APropertyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropertyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* HandleComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USoundWave* TipWave;

	UFUNCTION()
	void OnCollision(AActor* OverlapedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void ApplyToPlayer(class ABDemoPlayer* Player);

	virtual void ApplyToPlayer_Implementation(class ABDemoPlayer* Player);
};
