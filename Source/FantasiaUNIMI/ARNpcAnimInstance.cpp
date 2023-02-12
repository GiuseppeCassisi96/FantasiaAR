// Fill out your copyright notice in the Description page of Project Settings.


#include "ARNpcAnimInstance.h"



void UARNpcAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	DialoguePoint = TryGetPawnOwner();
}

void UARNpcAnimInstance::UpdateAnimationProperties()
{
	if(DialoguePoint)
	{
		bIsTalking = Cast<AARDialoguePoint>(DialoguePoint)->bDialogueIsStart;
	}
}


