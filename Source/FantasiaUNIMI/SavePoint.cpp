// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePoint.h"

#include "Components/WidgetSwitcher.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SaveTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SaveTrigger"));
	RootComponent = SaveTrigger;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SaveMesh"));
	MeshComponent->SetupAttachment(SaveTrigger);
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	SaveTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::SaveBegin);
	SaveTrigger->OnComponentEndOverlap.AddDynamic(this, &ASavePoint::SaveEnd);
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASavePoint::SaveBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("INIT"));
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TRIGGER"));
			hero->SaveGame();
			OnVisibleSaveText.Broadcast();
		}
	}
}

void ASavePoint::SaveEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero)
		{
			OnHiddenSaveText.Broadcast();
		}
	}
}

