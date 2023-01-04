// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "AREnemy.generated.h"

UCLASS()
class FANTASIAUNIMI_API AAREnemy : public ACharacter
{
	GENERATED_BODY()

public:
	enum State
	{
		Follow,
		Attack,
		Patrol
	};
	// Sets default values for this character's properties
	AAREnemy();
	UPROPERTY(EditAnywhere, Category = "Distances")
	double FollowDistance = 4.0f;
	UPROPERTY(EditAnywhere, Category = "Distances")
	double AttackDistance = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Hero")
	TSubclassOf<ACharacter> ARHeroClass;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> damageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	State currentState;
	UPROPERTY()
	APawn* ARHeroObj;
	FVector DistanceVector;
	FRotator rotation;
	UPROPERTY(EditAnywhere, Category= "Attack")
	float attackTime = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float attackDamage = 10.0f;
	FTimerHandle attackTimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ExecuteFSM();
	void CheckDistance(APawn* targetPawn);
	void SetState(State newState);
	void ApplyDamageHero();
	UFUNCTION()
	void TakeDamageEnemy(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a);
	
	
};


