// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ARHero.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ARChangeLevel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeLevelEvents, FString, text);
UCLASS()
class FANTASIAUNIMI_API AARChangeLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARChangeLevel();
	/**
	 * @brief The sphere trigger of change level obj
	 */
	UPROPERTY(EditAnywhere, Category="Trigger")
	USphereComponent* ChangeLevelTrigger;
	/**
	 * @brief The mesh of chenge level obj
	 */
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;
	/**
	 * @brief The level that will be loaded. The level will be loaded inside 'LevelMenu.cpp' file
	 */
	UPROPERTY(EditInstanceOnly, Category = "Level")
	TSoftObjectPtr<UWorld> NextLevel;
	/**
	 * @brief VFX of change level obj
	 */
	UPROPERTY(EditInstanceOnly, Category = "VFX")
	UNiagaraComponent* RingVFX;
	/**
	 * @brief Text of change level
	 */
	UPROPERTY(EditInstanceOnly, Category = "Text")
	FString ChangeLevelText;
	/**
	 * @brief Events that make the change level's UI visible or hidden
	 */
	FChangeLevelEvents OnNextLevelUI, OnEndNextLevelUI;
protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	/// <summary>
	/// it is a UFUNCTION that will be triggered when the player enters in the trigger. This function make visible
	///	the change level UI
	/// </summary>
	UFUNCTION()
	void BeginTrigger(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
	/// <summary>
	/// it is a UFUNCTION that will be triggered when the player exit from the trigger. This function hide the
	///	change level UI
	/// </summary>
	UFUNCTION()
	void EndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int otherBodyIndex);
};


