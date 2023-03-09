// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
//AnimiInstance for Enemies 
UCLASS()
class FANTASIAUNIMI_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable, Category= "AnimationUpdate")
	void UpdateAnimationProperties();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float movementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	APawn* animatedCharacter;
	
};
