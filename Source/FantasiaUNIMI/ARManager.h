// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AugmentedReality/Public/ARBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ARHero.h"
#include "ARWaypoint.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "ARManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIEvents);
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ARSessionData")
	UARSessionConfig* ARSession;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, Category = "Hero")
	TSubclassOf<AARHero> ARHero;
	UPROPERTY(EditDefaultsOnly, Category = "Touch interface")
	UTouchInterface* TouchInterface;
	
	UPROPERTY()
	AARHero* ARHeroObj;
	UPROPERTY(EditAnywhere, Category= "RootLevel")
	TSoftObjectPtr<APawn> ARLevelObj;
	UPROPERTY(EditAnywhere, Category= "Waypoints")
	TArray<TSoftObjectPtr<AActor>> wayPoints;
	UPROPERTY(BlueprintReadWrite)
	bool bScanIsComplete;
	UPROPERTY(BlueprintReadWrite)
	bool bIsSpawned;
	UPROPERTY(EditAnywhere, Category = "DialoguePoints")
	TArray<TSoftObjectPtr<AActor>> DialoguePoints;
	FUIEvents OnScanIsComplete;
	FUIEvents OnIsSpawned;
	FHeroMovements OnForwardMovement;
	FHeroMovements OnRightMovement;
	FHeroJump OnJump;
	FHeroAttack OnAttack;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UARTrackedGeometry* ARCorePlane;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsTracked;
	FTransform planeTr;
	FVector2D ScreenSize;
	UPROPERTY()
	TArray<UARTrackedGeometry*> Results;
	UPROPERTY()
	APlayerController* PlayerController;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void InputTouch(ETouchIndex::Type fingerIndex, FVector location);
	void ForwardMovement(float inputValue);
	void RightMovement(float inputValue);
	UFUNCTION()
	void JumpAction();
	UFUNCTION()
	void AttackAction();
};
