// Fill out your copyright notice in the Description page of Project Settings.


#include "ARHero.h"

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
	
}

// Called every frame
void AARHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

