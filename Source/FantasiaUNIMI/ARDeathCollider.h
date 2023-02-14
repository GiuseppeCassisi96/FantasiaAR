// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "ARHero.h"
#include "GameFramework/Actor.h"
#include "ARDeathCollider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvents);
UCLASS()
class FANTASIAUNIMI_API AARDeathCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARDeathCollider();
	UPROPERTY(EditAnywhere, Category = "DeathTrigger")
	UBoxComponent* DeathTrigger;
	UPROPERTY(EditInstanceOnly, Category = "DeathTrigger")
	TSoftObjectPtr<APawn> levelSpawn;
	FDeathEvents LoseOneSoulEvent, GameOverEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Death(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
};


