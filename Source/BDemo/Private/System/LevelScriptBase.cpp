// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LevelScriptBase.h"
#include "DataAsset/LevelDataAsset.h"
#include "Character/BDemoPlayer.h"
#include "System/EnemyBirthLocationMark.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void ALevelScriptBase::BeginPlay()
{
	Super::BeginPlay();
	GenerateLevel(LevelDataAsset);
}

void ALevelScriptBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ALevelScriptBase::GenerateLevel(class ULevelDataAsset* GenerateDataAsset)
{
	Level = Cast<ULevel>(UKismetSystemLibrary::GetOuterObject(this));
	World = Cast<UWorld>(Level->GetOuter());
	if (Level == nullptr || World == nullptr || GenerateDataAsset == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Level Fine!")));
		return;
	}
	const TArray<TSubclassOf<AActor>>& Enemies = GenerateDataAsset->Enemies;
	
	GenerateEnemies(Enemies);

}

void ALevelScriptBase::GenerateEnemies(const TArray<TSubclassOf<AActor>>& Enemies)
{
	TArray<AActor*> EnemyMarks;
	GetAllActorsOfTag(Level->Actors, EnemyMarks, FName(TEXT("EnemyBirthLocationMark")));
	if (Enemies.Num() == 0 || EnemyMarks.Num() == 0)
	{
		return;
	}
	for (int32 i = 0; i < EnemyMarks.Num(); i++)
	{
		AActor* RandomLocationActor = EnemyMarks[i];
		TSubclassOf<AActor> RandomType = GetRandomItem(Enemies);
		FTransform Transform = RandomLocationActor->GetActorTransform();
		SpawnActor(RandomType, Transform);
	}
}

AActor* ALevelScriptBase::SpawnActor(TSubclassOf<AActor> ActorClass, const FTransform& Transform)
{
	return World->SpawnActor<AActor>(ActorClass, Transform);
}

void ALevelScriptBase::GetAllActorsOfTag(const TArray<AActor*>& ActorArray, TArray<AActor*>& Result, const FName& Tag)
{
	for (AActor* Actor : ActorArray)
	{							   
		if (Actor->Tags.Contains(Tag))
		{
			Result.Add(Actor);
		}
	}
}
