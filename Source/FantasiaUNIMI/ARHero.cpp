// Fill out your copyright notice in the Description page of Project Settings.


#include "ARHero.h"

#include "ARBlueprintLibrary.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AARHero::AARHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AARHero::BeginPlay()
{
	Super::BeginPlay();
	rotation = FRotator::ZeroRotator;
	direction = FVector::Zero();
	OnTakeAnyDamage.AddUniqueDynamic(this, &AARHero::TakeDamageFromEnemy);
	Actors.Add(this);
	HeroAnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AARHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(FRotator(0.0f, rotation.Yaw, 0.0f));
	
}

// Called to bind functionality to input
void AARHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AARHero::ForwardMovement(float inputValue, FVector ARCameraFowardAxe)
{
	AddMovementInput(ARCameraFowardAxe, inputValue
		* Speed * GetWorld()->GetDeltaSeconds());
	rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector,
		GetMovementComponent()->Velocity);
}

void AARHero::RightMovement(float inputValue, FVector ARCameraRightAxe)
{
	AddMovementInput(ARCameraRightAxe, inputValue
		* Speed * GetWorld()->GetDeltaSeconds());
	rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ForwardVector,
		GetMovementComponent()->Velocity);
}

void AARHero::JumpAction()
{
	Jump();
}


void AARHero::ApplyDamageToEnemy()
{
	UGameplayStatics::ApplyRadialDamage(this, 10.0f, GetActorLocation(),
		attackRadius, damageType, Actors);
}

void AARHero::TakeDamageFromEnemy(AActor* Actor, float damage, const UDamageType* type, AController* Contr, AActor* a)
{
	heroLife -= damage;
	UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
	if (heroLife <= 0)
	{
		heroSouls--;
		heroLife = 100;
		if(heroSouls <= 0)
		{
			UARBlueprintLibrary::StopARSession();
			UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
			return;
		}
		SoulsUpdate.Broadcast();
	}
	LifeUpdate.Broadcast();
}

void AARHero::Attack()
{
	if(!bAttackState)
	{
		bAttackState = true;
		HeroAnimInstance->Montage_Play(AttackMontage);
		HeroAnimInstance->Montage_JumpToSection(FName("Attack"));
	}
}


void AARHero::IncrementCoin()
{
	numberOfCoin++;
	if(numberOfCoin >= 10)
	{
		numberOfCoin = 0;
		if(heroLife <= 90)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), PowerUpSound);
			heroLife += 10;
			LifeUpdate.Broadcast();
		}
		
	}
}

void AARHero::SaveGame()
{
	UARSaveGame* SaveGameInstance = Cast<UARSaveGame>(UGameplayStatics::CreateSaveGameObject(
		UARSaveGame::StaticClass()));
	SaveGameInstance->CharacterData.life = heroLife;
	SaveGameInstance->CharacterData.coin = numberOfCoin;
	SaveGameInstance->CharacterData.souls = heroSouls;
	SaveGameInstance->CharacterData.LevelToLoad = GetWorld();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->UserName, 
		SaveGameInstance->UserIndex);
}

void AARHero::LoadGame()
{
	UARSaveGame* LoadGameInstance = Cast<UARSaveGame>(UGameplayStatics::CreateSaveGameObject(
		UARSaveGame::StaticClass()));
	LoadGameInstance = Cast<UARSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->UserName, 
		LoadGameInstance->UserIndex));
	if (LoadGameInstance != nullptr && GetWorld() == LoadGameInstance->CharacterData.LevelToLoad)
	{
		heroLife = LoadGameInstance->CharacterData.life;
		numberOfCoin = LoadGameInstance->CharacterData.coin;
		heroSouls = LoadGameInstance->CharacterData.souls;
	}
}


