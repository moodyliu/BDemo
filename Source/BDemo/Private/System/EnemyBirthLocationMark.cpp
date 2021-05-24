// Fill out your copyright notice in the Description page of Project Settings.


#include "System/EnemyBirthLocationMark.h"

// Sets default values
AEnemyBirthLocationMark::AEnemyBirthLocationMark()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = SceneComp;
	Tags.Add(FName(TEXT("EnemyBirthLocationMark")));
}

// Called when the game starts or when spawned
void AEnemyBirthLocationMark::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBirthLocationMark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

