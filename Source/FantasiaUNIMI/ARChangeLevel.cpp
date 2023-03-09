// Fill out your copyright notice in the Description page of Project Settings.


#include "ARChangeLevel.h"

#include "ARBlueprintLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AARChangeLevel::AARChangeLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChangeLevelTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("ChangeLevelTrigger"));
	RootComponent = ChangeLevelTrigger;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeLevelMesh"));
	MeshComponent->SetupAttachment(ChangeLevelTrigger);
	RingVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RingVFX"));
	RingVFX->SetupAttachment(ChangeLevelTrigger);
}

// Called when the game starts or when spawned
void AARChangeLevel::BeginPlay()
{
	Super::BeginPlay();
	ChangeLevelTrigger->OnComponentBeginOverlap.AddDynamic(this, &AARChangeLevel::BeginTrigger);
	ChangeLevelTrigger->OnComponentEndOverlap.AddDynamic(this, &AARChangeLevel::EndTrigger);
}

// Called every frame
void AARChangeLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AARChangeLevel::BeginTrigger(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero)
		{
			OnNextLevelUI.Broadcast(ChangeLevelText);
		}
	}
	
}

void AARChangeLevel::EndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero)
		{
			OnEndNextLevelUI.Broadcast(TEXT(""));
		}
	}
}
