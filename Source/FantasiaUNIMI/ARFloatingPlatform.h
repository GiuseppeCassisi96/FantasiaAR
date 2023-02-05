// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ARFloatingPlatform.generated.h"

UCLASS()
class FANTASIAUNIMI_API AARFloatingPlatform : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AARFloatingPlatform();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "PlatformMesh")
	UStaticMeshComponent* Platform;
	UPROPERTY(EditInstanceOnly, Category = "Speed")
	float speed = 7;
	UPROPERTY(EditInstanceOnly, Category = "Amplitude");
	float amplitude;
	UPROPERTY(EditInstanceOnly, Category = "Direction")
	FVector MoveDir {1.0f, 0.0f, 0.0f};
	float iteration = 0.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
