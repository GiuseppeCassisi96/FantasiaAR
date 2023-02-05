// Fill out your copyright notice in the Description page of Project Settings.


#include "AREnemy.h"

#include "ARHero.h"


// Sets default values
AAREnemy::AAREnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	followSphere = CreateDefaultSubobject<USphereComponent>(TEXT("FollowSphere"));
	combatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	followSphere->SetupAttachment(RootComponent);
	combatSphere->SetupAttachment(RootComponent);
	minAttackTime = 1.0f;
	maxAttackTime = 4.0f;
	enemyState = EFSMState::EFSM_Idle;
}

// Called when the game starts or when spawned
void AAREnemy::BeginPlay()
{
	Super::BeginPlay();
	followSphere->OnComponentBeginOverlap.AddDynamic(this, &AAREnemy::FollowBegin);
	combatSphere->OnComponentBeginOverlap.AddDynamic(this, &AAREnemy::CombatBegin);
	followSphere->OnComponentEndOverlap.AddDynamic(this, &AAREnemy::FollowEnd);
	combatSphere->OnComponentEndOverlap.AddDynamic(this, &AAREnemy::CombatEnd);
	ARHeroObj =  static_cast<APawn*>(UGameplayStatics::GetActorOfClass(this,
		ARHeroClass));
	OnTakeAnyDamage.AddDynamic(this, &AAREnemy::TakeDamageFromHero);
	EnemyAnimInstance = static_cast<UMainAnimInstance*>(GetMesh()->GetAnimInstance());
	AttackTimerDelegate.BindUFunction(this, "Attack");
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
	DistanceVector = UKismetMathLibrary::Vector_NormalUnsafe( targetPawn->GetActorLocation() - GetActorLocation());
}


void AAREnemy::ExecuteFSM()
{
	CheckDistance(ARHeroObj);
	if(enemyState == EFSMState::EFSM_Follow)
	{
		if(!bIsAttacking)
		{
			AddMovementInput(DistanceVector, 1.0f * speed *
				GetWorld()->GetDeltaSeconds());
			rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector,
				GetMovementComponent()->Velocity);
		}
		GetWorldTimerManager().ClearTimer(attackTimer);
	}
}

void AAREnemy::ApplyDamageToHero()
{
	if(enemyState == EFSMState::EFSM_Attack && enemyState != EFSMState::EFSM_Dead)
	{
		UGameplayStatics::ApplyDamage(ARHeroObj, attackDamage,
			GetController(), this, damageType);
		float attackTime = FMath::RandRange(minAttackTime, maxAttackTime);
		GetWorldTimerManager().SetTimer(attackTimer, AttackTimerDelegate,attackTime,false);
	}
		
}

void AAREnemy::TakeDamageFromHero(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a)
{
	SetState(EFSMState::EFSM_Dead);
	UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
	EnemyAnimInstance->Montage_Play(CombatMontage);
	EnemyAnimInstance->Montage_JumpToSection(FName("Death"));
}

void AAREnemy::Attack()
{
	bIsAttacking = true;
	if(EnemyAnimInstance && enemyState != EFSMState::EFSM_Dead)
	{
		EnemyAnimInstance->Montage_Play(CombatMontage);
		EnemyAnimInstance->Montage_JumpToSection(FName("Attack1"), CombatMontage);
	}
}

void AAREnemy::FollowBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
	int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero && enemyState != EFSMState::EFSM_Dead)
		{
			SetState(EFSMState::EFSM_Follow);
		}
	}
}

void AAREnemy::FollowEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, 
	UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero && enemyState != EFSMState::EFSM_Dead)
		{
			SetState(EFSMState::EFSM_Idle);
		}
	}
}

void AAREnemy::CombatBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
                           int otherBodyIndex, bool fromSweep, const FHitResult& sweepResults)
{
	if(otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if(hero && enemyState != EFSMState::EFSM_Dead)
		{
			SetState(EFSMState::EFSM_Attack);
			float attackTime = FMath::RandRange(minAttackTime, maxAttackTime);
			GetWorldTimerManager().SetTimer(attackTimer, AttackTimerDelegate, attackTime, false);
		}
	}
	
}

void AAREnemy::CombatEnd(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if (otherActor)
	{
		AARHero* hero = Cast<AARHero>(otherActor);
		if (hero && enemyState != EFSMState::EFSM_Dead)
		{
			bIsAttacking = false;
			SetState(EFSMState::EFSM_Follow);
		}
	}
}









