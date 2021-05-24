// Fill out your copyright notice in the Description page of Project Settings.


#include "Attackable/PingpongObstacle.h"
#include "DataAsset/EnemyDataAsset.h"
#include "System/LevelScriptBase.h"

void APingpongObstacle::OnReceiveDamage_Implementation(int DamageValue)
{
	if (EnemyDataAsset)
	{
		if ( FMath::RandRange(0, 100) <= EnemyDataAsset->SpawnChance )
		{
			SpawnRandomProperty();
		}
	}
	Destroy();
}

void APingpongObstacle::BeginPlay()
{
	Super::BeginPlay();
	MoveToTarget(LocationMark1);
}

void APingpongObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetMark == nullptr) return;
	if (TargetMark->GetRelativeLocation() == Mesh->GetRelativeLocation())
	{
		if (TargetMark == LocationMark1)
		{
			MoveToTarget(LocationMark2);
		}
		else
		{
			MoveToTarget(LocationMark1);
		}
	}
	Mesh->SetRelativeLocation(FMath::VInterpConstantTo(Mesh->GetRelativeLocation(), TargetMark->GetRelativeLocation(), DeltaTime, InterpSpeed));
}

void APingpongObstacle::MoveToTarget(USceneComponent* Target)
{
	TargetMark = Target;
}

void APingpongObstacle::SpawnRandomProperty()
{
	if (!EnemyDataAsset || EnemyDataAsset->SpawnProperties.Num() <= 0) return;
	ALevelScriptBase* ScriptActor = Cast<ALevelScriptBase>(GetLevel()->GetLevelScriptActor());
	if (ScriptActor)
	{
		ScriptActor->SpawnActor(ALevelScriptBase::GetRandomItem(EnemyDataAsset->SpawnProperties), GetActorTransform());
	}
	else
	{
		FTransform Trans = GetActorTransform();
		GetWorld()->SpawnActor(ALevelScriptBase::GetRandomItem(EnemyDataAsset->SpawnProperties), &Trans);
	}
}

APingpongObstacle::APingpongObstacle()
{
	LocationMark1 = CreateDefaultSubobject<USceneComponent>("LocationMark1");
	LocationMark1->SetupAttachment(RootComponent);

	LocationMark2 = CreateDefaultSubobject<USceneComponent>("LocationMark2");
	LocationMark2->SetupAttachment(RootComponent);
}
