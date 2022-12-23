// Fill out your copyright notice in the Description page of Project Settings.


#include "ARHero.h"

#include "Components/ArrowComponent.h"

// Sets default values
AARHero::AARHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARHero::BeginPlay()
{
	Super::BeginPlay();
	rotation = FRotator::ZeroRotator;
	oldPos = FVector::Zero();
	newPos = FVector::Zero();
	direction = FVector::Zero();
}

// Called every frame
void AARHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(FRotator(0.0f, rotation.Yaw, 0.0f));
}

// Called to bind functionality to input
void AARHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AARHero::ForwardMovement(float inputValue, FVector ARCameraFowardAxe)
{
	AddMovementInput(ARCameraFowardAxe, inputValue
		* Speed * GetWorld()->GetDeltaSeconds());
	if (GetMovementComponent()->Velocity != FVector::Zero())
	{
		rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector, 
			GetMovementComponent()->Velocity);
	}
}

void AARHero::RightMovement(float inputValue, FVector ARCameraRightAxe)
{
	AddMovementInput(ARCameraRightAxe, inputValue
		* Speed * GetWorld()->GetDeltaSeconds());
	if (GetMovementComponent()->Velocity != FVector::Zero())
	{
		rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector, 
			GetMovementComponent()->Velocity);
		
	}

}

void AARHero::JumpAction()
{
	Jump();
}

void AARHero::StopJumpAction()
{
	StopJumping();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
		TEXT("STOP"));
}

