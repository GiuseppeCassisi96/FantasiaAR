// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARHero.h"
#include "Components/SphereComponent.h"
#include "SavePoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSaveUIEvents);

UCLASS()
class FANTASIAUNIMI_API ASavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavePoint();
	UPROPERTY(EditAnywhere, Category="Trigger")
	USphereComponent* SaveTrigger;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;
	FSaveUIEvents OnVisibleSaveText;
	FSaveUIEvents OnHiddenSaveText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void SaveBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
	UFUNCTION()
	void SaveEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int otherBodyIndex);
};
