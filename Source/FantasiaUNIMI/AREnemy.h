// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Animation/AnimNode_StateMachine.h"
#include "MainAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "AREnemy.generated.h"


enum class EFSMState
{
	EFSM_Follow,
	EFSM_Attack,
	EFSM_Idle
};

UCLASS()
class FANTASIAUNIMI_API AAREnemy : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	AAREnemy();
	UPROPERTY(EditDefaultsOnly, Category = "Distances")
	double FollowDistance = 4.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Distances")
	double AttackDistance = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Hero")
	TSubclassOf<ACharacter> ARHeroClass;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float speed = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float minAttackTime;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float maxAttackTime;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float attackDamage = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly,Category="IA")
	USphereComponent* followSphere;
	UPROPERTY(EditDefaultsOnly, Category = "IA")
	USphereComponent* combatSphere;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	APawn* ARHeroObj;
	UPROPERTY()
	UMainAnimInstance* EnemyAnimInstance;
	FTimerDelegate TimerFunctionDelegate{};
	EFSMState enemyState;
	FVector DistanceVector;
	FRotator rotation;
	FTimerHandle attackTimer;
	bool bIsAttacking;
	


public:	
	FORCEINLINE void SetState(EFSMState newState) { enemyState = newState; }
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToHero();
	UFUNCTION()
	void TakeDamageFromHero(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a);
	UFUNCTION()
		void FollowBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
	UFUNCTION()
		void FollowEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex);
	UFUNCTION()
		void CombatBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
	UFUNCTION()
		void CombatEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int otherBodyIndex);
	UFUNCTION()
	void Attack();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ExecuteFSM();
	void CheckDistance(APawn* targetPawn);
	
	
};


