// Fill out your copyright notice in the Description page of Project Settings.


#include "ARDialoguePoint.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AARDialoguePoint::AARDialoguePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DialogueSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	RootComponent = DialogueSphere;
	NPCBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCSKMesh"));
	NPCBody->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AARDialoguePoint::BeginPlay()
{
	Super::BeginPlay();
	DialogueSphere->OnComponentBeginOverlap.AddDynamic(this, &AARDialoguePoint::DialogueBegin);
	DialogueSphere->OnComponentEndOverlap.AddDynamic(this, &AARDialoguePoint::DialogueEnd);
}

// Called every frame
void AARDialoguePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARDialoguePoint::DialogueBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero)
		{
			OnStartDialogue.Broadcast(dialogues, this);
			bDialogueIsStart = true;
		}
	}
}

void AARDialoguePoint::DialogueEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero)
		{
			OnEndDialogue.Broadcast(this);
			bDialogueIsStart = false;
		}
	}
}


