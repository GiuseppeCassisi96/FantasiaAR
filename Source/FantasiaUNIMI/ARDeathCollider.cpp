// Fill out your copyright notice in the Description page of Project Settings.


#include "ARDeathCollider.h"

#include "ARBlueprintLibrary.h"

// Sets default values
AARDeathCollider::AARDeathCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathCollider"));
	RootComponent = DeathTrigger;
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &AARDeathCollider::Death);
}

// Called when the game starts or when spawned
void AARDeathCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARDeathCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AARDeathCollider::Death(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HERO"));
			hero->heroSouls--;
			if(hero->heroSouls <= 0)
			{
				UARBlueprintLibrary::StopARSession();
				UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
				return;
			}
			hero->SoulsUpdate.Broadcast();
			otherActor->SetActorLocation(levelSpawn.Get()->GetActorLocation());
		}
		

	}
}