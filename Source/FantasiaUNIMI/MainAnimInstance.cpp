// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	if(animatedCharacter == nullptr)
	{
		//I'm getting the pawn owner of this anim instance
		animatedCharacter = TryGetPawnOwner();
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	//I Update properties that are useful for animations 
	if(animatedCharacter)
	{
		FVector speed = animatedCharacter->GetVelocity();
		FVector groundSpeed = FVector(speed.X, speed.Y, 0.0f);
		movementSpeed = groundSpeed.Size();
		bIsInAir = animatedCharacter->GetMovementComponent()->IsFalling();
	}

}

