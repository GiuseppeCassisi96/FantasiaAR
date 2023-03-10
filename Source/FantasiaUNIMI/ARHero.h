// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ARSaveGame.h"
#include "AREnemy.h"
#include "Sound/SoundCue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "ARHero.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeroProperties);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS()
class FANTASIAUNIMI_API AARHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARHero();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HeroSpeed")
	float Speed = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditDefaultsOnly, Category = "ApplyDamageToEnemy")
	float attackTime = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = "ApplyDamageToEnemy")
	float attackDamage = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "ApplyDamageToEnemy")
	float attackRadius = 14.0f;
	UPROPERTY(BlueprintReadWrite, Category="AnimState")
	bool bAttackState;
	UPROPERTY(EditDefaultsOnly, Category= "Life")
	int heroLife;
	UPROPERTY(EditDefaultsOnly, Category = "Life")
	int heroSouls;
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* HitSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* PowerUpSound;
	int numberOfCoin;
	TSoftObjectPtr<UUserWidget> LevelMenu;
	FHeroProperties OnLifeUpdate;
	FHeroProperties OnCoinUpdate;
	FHeroProperties OnSoulsUpdate;
	FDeath OnDeathEvent;
	bool isDead = false;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FRotator rotation;
	FVector direction;
	UPROPERTY()
	TArray<AActor*> Actors;

	UPROPERTY()
	UAnimInstance* HeroAnimInstance;
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
	//is called inside animBP associated to this CharacterBP
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToEnemy();
	UFUNCTION()
	void TakeDamageFromEnemy(AActor* DamagedActor, float Damage, const UDamageType* TypeOfDamage, AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
	void Attack();

	void IncrementCoin();
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
};



