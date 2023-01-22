// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ARHero.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ARChangeLevel.generated.h"

UCLASS()
class FANTASIAUNIMI_API AARChangeLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARChangeLevel();
	UPROPERTY(EditAnywhere, Category="Trigger")
	USphereComponent* ChangeLevelTrigger;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditInstanceOnly, Category = "Level")
	TSoftObjectPtr<UWorld> NextLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void BeginTrigger(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
};


