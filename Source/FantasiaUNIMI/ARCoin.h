// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARHero.h"
#include <Components/SphereComponent.h>

#include "Sound/SoundCue.h"
#include "ARCoin.generated.h"

UCLASS()
class FANTASIAUNIMI_API AARCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARCoin();
	UPROPERTY(EditDefaultsOnly, Category = "CoinTrigger")
	USphereComponent* CoinTrigger;
	UPROPERTY(EditDefaultsOnly, Category = "CoinMesh")
	UStaticMeshComponent* CoinMesh;
	UPROPERTY(EditDefaultsOnly, Category = "RotationSpeed")
	float rotationSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* CoinSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void TakeTheCoin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
};
