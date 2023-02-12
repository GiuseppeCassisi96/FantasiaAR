// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARDialoguePoint.h"
#include "Animation/AnimInstance.h"
#include "ARNpcAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FANTASIAUNIMI_API UARNpcAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Talking")
	bool bIsTalking;
	virtual  void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();
	APawn* DialoguePoint;
};
