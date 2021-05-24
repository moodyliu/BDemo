// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelScriptBase.generated.h"

/**
 * 
 */
UCLASS()
class BDEMO_API ALevelScriptBase : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void GenerateLevel(class ULevelDataAsset* GenerateDataAsset);

	void GenerateEnemies(const TArray<TSubclassOf<AActor>>& Enemies);

	void GetAllActorsOfTag(const TArray<AActor*>& ActorArray, TArray<AActor*>& Result,const FName& Tag);

	UPROPERTY(EditAnywhere)
	class ULevelDataAsset* LevelDataAsset;

	class ULevel* Level;
	class UWorld* World;

public:
	template<class T>
	static T GetRandomItem(const TArray<T>& Array);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnActor(TSubclassOf<AActor> ActorClass, const FTransform& Transform);
};

template<class T>
T ALevelScriptBase::GetRandomItem(const TArray<T>& Array)
{
	int32 RandomIndex = FMath::RandRange(0, Array.Num() - 1);
	return Array[RandomIndex];
}
