// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "ARWaypoint.generated.h"

//Class responsible for spawning enemies
UCLASS()
class FANTASIAUNIMI_API AARWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARWaypoint();
	UPROPERTY(EditAnywhere, Category="Enemy class")
	TSubclassOf<ACharacter> AREnemyClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawCharacter();
};
