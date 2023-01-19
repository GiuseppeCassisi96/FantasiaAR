// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float attackTime = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float attackDamage = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float attackRadius = 14.0f;
	FTimerHandle attackTimerHandle;
	bool bCanAttack = true;
	UPROPERTY(EditDefaultsOnly, Category= "Life")
	int heroLife;
	int numberOfCoin;
	TSoftObjectPtr<UUserWidget> LevelMenu;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FRotator rotation;
	FVector oldPos, newPos, direction;
	UPROPERTY()
	TArray<AActor*> Actors;
	FTimerDelegate TimerFunctionDelegate{};
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ForwardMovement(float inputValue, FVector ARCameraFowardAxe);
	UFUNCTION()
	void RightMovement(float inputValue, FVector ARCameraRightAxe);
	UFUNCTION()
	void JumpAction();
	UFUNCTION()
	void Attack();
	UFUNCTION()
	void TakeDamageHero(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a);
	UFUNCTION()
	void SetbCanAttack();
};



