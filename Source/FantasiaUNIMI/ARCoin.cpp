// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCoin.h"

#include "Components/AudioComponent.h"

// Sets default values
AARCoin::AARCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CoinTrigger = CreateDefaultSubobject<USphereComponent>("CoinCollider");
	RootComponent = CoinTrigger;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("CoinMesh");
	CoinMesh->SetupAttachment(CoinTrigger);
	
}

// Called when the game starts or when spawned
void AARCoin::BeginPlay()
{
	Super::BeginPlay();
	CoinTrigger->OnComponentBeginOverlap.AddDynamic(this, &AARCoin::TakeTheCoin);
}

// Called every frame
void AARCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, 1.0f, 0.0f) * rotationSpeed * GetWorld()->GetDeltaSeconds());

}

void AARCoin::TakeTheCoin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CoinSound);
			hero->IncrementCoin();
			hero->CoinUpdate.Broadcast();
			Destroy();
		}
	}
}

