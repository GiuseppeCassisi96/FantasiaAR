// Fill out your copyright notice in the Description page of Project Settings.


#include "ARFloatingPlatform.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AARFloatingPlatform::AARFloatingPlatform()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = Platform;
	
}

// Called when the game starts or when spawned
void AARFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Direction;
	Direction = MoveDir * UKismetMathLibrary::Sin(iteration) * speed;
	AddActorLocalOffset(Direction);
	iteration += 1/amplitude;
}

// Called to bind functionality to input
void AARFloatingPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

