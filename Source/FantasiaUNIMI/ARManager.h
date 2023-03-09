// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AugmentedReality/Public/ARBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ARHero.h"
#include "Sound/SoundCue.h"
#include "ARWaypoint.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "ARManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FARSessionEvents);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHeroMovements, float, inputValue, FVector, cameraAxe);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeroJump);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeroAttack);

UCLASS()
class FANTASIAUNIMI_API AARManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AARManager();
	/**
	 * @brief Contains the ARSessionConfig data
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ARSessionData")
	UARSessionConfig* ARSession;
	/**
	 * @brief Camera of ARManager, it will move according to the movement of phone and capture the entire scene 
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent;
	/**
	 * @brief The class of hero obj
	 */
	UPROPERTY(EditAnywhere, Category = "Hero")
	TSubclassOf<AARHero> ARHero;
	/**
	 * @brief Touch interface that contains left stick
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Touch interface")
	UTouchInterface* TouchInterface;

	UPROPERTY()
	AARHero* ARHeroObj;
	/**
	 * @brief Current sound of world
	 */
	UPROPERTY(EditInstanceOnly, Category="Sound")
	USoundCue* WorldSound;
	/**
	 * @brief Root element of level. The other level's elements are children of that Root element
	 */
	UPROPERTY(EditAnywhere, Category= "RootLevel")
	TSoftObjectPtr<APawn> ARLevelObj;
	/**
	 * @brief Array of waypoints responsible for Enemies spawn 
	 */
	UPROPERTY(EditAnywhere, Category= "Waypoints")
	TArray<TSoftObjectPtr<AActor>> wayPoints;
	UPROPERTY(BlueprintReadWrite)
	bool bScanIsComplete;
	UPROPERTY(BlueprintReadWrite)
	bool bIsSpawned;
	/**
	 * @brief An array of all dialogue points present in the level
	 */
	UPROPERTY(EditAnywhere, Category = "DialoguePoints")
	TArray<TSoftObjectPtr<AActor>> DialoguePoints;
	/**
	 * @brief A reference to the save point
	 */
	UPROPERTY(EditAnywhere, Category = "SavePoint")
	TSoftObjectPtr<AActor> SavePoint;

	/**
	 * @brief Event that will be executed when the scan will be completed
	 */
	FARSessionEvents OnScanIsComplete;
	/**
	 * @brief Event that will be executed when the level will be spawned 
	 */
	FARSessionEvents OnIsSpawned;
	/**
	 * @brief Events responsible for the character's movement 
	 */
	FHeroMovements OnForwardMovement, OnRightMovement;
	/**
	 * @brief Event responsible for the character's jump
	 */
	FHeroJump OnJump;
	/**
	 * @brief Event responsible for the character's attack
	 */
	FHeroAttack OnAttack;
protected:
	/**
	 * @brief It is the plane where the level will be spawned 
	 */
	UPROPERTY()
	UARTrackedGeometry* ARCorePlane;
	/**
	 * @brief Transform of plane
	 */
	FTransform planeTr;
	FVector2D ScreenSize;
	/**
	 * @brief Results of geometry tracking 
	 */
	UPROPERTY()
	TArray<UARTrackedGeometry*> Results;
	UPROPERTY()
	APlayerController* PlayerController;

	virtual void BeginPlay() override;
public:
	/**
	 * @brief Input function that will be triggered when the player touch the screen 
	 */
	void InputTouch(ETouchIndex::Type fingerIndex, FVector location);
	/**
	 * @brief Will be triggered when I move forward or backward the left stick. Trigger an event
	 * that moves the player backward or forward
	 * @param inputValue This value depends how much I move forward or backward the left stick
	 */
	void ForwardMovement(float inputValue);
	/**
	 * @brief Will be triggered when I move right or left the left stick. Trigger an event
	 * that moves the player right or left
	 * @param inputValue This value depends how much I move right or left the left stick
	 */
	void RightMovement(float inputValue);
	/**
	 * @brief Will be triggered when I press the jump button. Trigger an event
	 * that makes the player jump
	 */
	UFUNCTION()
	void JumpAction();
	/**
	 * @brief Will be triggered when I press the attack button. Trigger an event
	 * that makes the player attack
	 */
	UFUNCTION()
	void AttackAction();


	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
