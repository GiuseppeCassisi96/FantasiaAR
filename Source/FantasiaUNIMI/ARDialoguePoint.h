// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ARDialoguePoint.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartDialogueEvent, TArray<FString>, dialogues, AActor*, dialoguePoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDialogueEvent, AActor*, dialoguePoint);
UCLASS()
class FANTASIAUNIMI_API AARDialoguePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARDialoguePoint();
	UPROPERTY(EditDefaultsOnly, Category="Trigger")
	USphereComponent* DialogueSphere;
	UPROPERTY(EditDefaultsOnly, Category = "Trigger")
	UStaticMeshComponent* DialogueMesh;
	
	UPROPERTY(EditInstanceOnly, Category="Dialogues")
	TArray<FString> dialogues;
	FStartDialogueEvent StartDialogue;
	FEndDialogueEvent EndDialogue;
	int dialogueIndex;
	bool bDialogueIsComplete;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void DialogueBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults);
	UFUNCTION()
	void DialogueEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int otherBodyIndex);
};
