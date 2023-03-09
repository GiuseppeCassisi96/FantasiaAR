// Fill out your copyright notice in the Description page of Project Settings.


#include "ARWaypoint.h"


// Sets default values
AARWaypoint::AARWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARWaypoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Will be called by ARManager instance 
void AARWaypoint::SpawCharacter()
{
	const FVector spawnLocation = GetActorLocation();
	const FRotator spawnRotation = GetActorRotation();
	GetWorld()->SpawnActor(AREnemyClass, &spawnLocation, &spawnRotation);
}

