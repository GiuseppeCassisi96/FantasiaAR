// Fill out your copyright notice in the Description page of Project Settings.


#include "AREnemy.h"

#include "TimerManager.h"


// Sets default values
AAREnemy::AAREnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAREnemy::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(attackTimerHandle, this,
		&AAREnemy::ApplyDamageHero, attackTime,true);
	GetWorldTimerManager().PauseTimer(attackTimerHandle);
	ARHeroObj =  static_cast<APawn*>(UGameplayStatics::GetActorOfClass(this,
		ARHeroClass));
	OnTakeAnyDamage.AddUniqueDynamic(this, &AAREnemy::TakeDamageEnemy);
}

// Called every frame
void AAREnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ExecuteFSM();
	SetActorRotation(FRotator(0.0f, rotation.Yaw, 0.0f));
}

// Called to bind functionality to input
void AAREnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAREnemy::CheckDistance(APawn* targetPawn)
{
	const double distance = UKismetMathLibrary::Vector_Distance
	(GetActorLocation(), targetPawn->GetActorLocation());
	DistanceVector = UKismetMathLibrary::Vector_NormalUnsafe( targetPawn->GetActorLocation() - GetActorLocation());
	if(distance <= FollowDistance && distance > AttackDistance)
	{
		SetState(Follow);
	}
	else if(distance > FollowDistance)
	{
		SetState(Patrol);
	}
	else if(distance <= AttackDistance)
	{
		SetState(Attack);
	}
}

void AAREnemy::ExecuteFSM()
{
	CheckDistance(ARHeroObj);
	if(currentState == Patrol)
	{
		//Do patrol....
		GetWorldTimerManager().PauseTimer(attackTimerHandle);
	}
	else if(currentState == Follow)
	{
		GetWorldTimerManager().PauseTimer(attackTimerHandle);
		AddMovementInput(DistanceVector, 1.0f * speed *
			GetWorld()->GetDeltaSeconds());
		rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector,
			GetMovementComponent()->Velocity);
	}
	else if(currentState == Attack)
	{
		GetWorldTimerManager().UnPauseTimer(attackTimerHandle);
	}
}

void AAREnemy::SetState(State newState)
{
	currentState = newState;
}

void AAREnemy::ApplyDamageHero()
{
	if(currentState == Attack)
		UGameplayStatics::ApplyDamage(ARHeroObj, attackDamage,
		GetController(), this, damageType);
	
}

void AAREnemy::TakeDamageEnemy(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Goblin che male"));
}










