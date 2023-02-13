// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ARHero.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "ARDialoguePoint.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartDialogueEvent, TArray<FString>, dialogues, AActor*, dialoguePoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDialogueEvent, AActor*, dialoguePoint);
UCLASS()
class FANTASIAUNIMI_API AARDialoguePoint : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARDialoguePoint();
	UPROPERTY(EditAnywhere, Category="Trigger")
	USphereComponent* DialogueSphere;
	
	UPROPERTY(EditInstanceOnly, Category="Dialogues")
	TArray<FString> dialogues;
	UPROPERTY(EditInstanceOnly, Category = "SkeletalMesh")
	USkeletalMeshComponent* NPCBody;
	UPROPERTY(BlueprintReadOnly, Category="Dialogues")
	bool bDialogueIsStart;
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
