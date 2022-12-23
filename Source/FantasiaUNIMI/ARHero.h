// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "ARHero.generated.h"

UCLASS()
class FANTASIAUNIMI_API AARHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARHero();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HeroSpeed")
	float Speed = 10.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FRotator rotation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ForwardMovement(float inputValue, FVector ARCameraFowardAxe);
	void RightMovement(float inputValue, FVector ARCameraRightAxe);
	void JumpAction();
	void StopJumpAction();

};
