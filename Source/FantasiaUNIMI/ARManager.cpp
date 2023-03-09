// Fill out your copyright notice in the Description page of Project Settings.


#include "ARManager.h"

// Sets default values
AARManager::AARManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = CameraComponent;
}

// Called when the game starts or when spawned
void AARManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(this);
	PlayerController->ActivateTouchInterface(nullptr);
	bScanIsComplete = false;
	bIsSpawned = false;
}

// Called every frame
void AARManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Here I scan the environment
	if (!bScanIsComplete)
	{
		Results = UARBlueprintLibrary::GetAllGeometries();
		if (Results.Num() > 0)
		{
			bScanIsComplete = true;
			OnScanIsComplete.Broadcast();
		}
	}
}

// Called to bind functionality to input
void AARManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AARManager::InputTouch);
	PlayerInputComponent->BindAxis("Horizontal", this, &AARManager::RightMovement);
	PlayerInputComponent->BindAxis("Vertical", this, &AARManager::ForwardMovement);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed,
		this, &AARManager::JumpAction);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed,
		this, &AARManager::AttackAction);
}


void AARManager::InputTouch(ETouchIndex::Type fingerIndex, FVector location)
{
	
	if (bScanIsComplete && !bIsSpawned)
	{
		
		bool isCurrentlyPressed;
		PlayerController->GetInputTouchState(fingerIndex, location.X, location.Y, isCurrentlyPressed);
		FVector WorldLocation, Direction;
		PlayerController->DeprojectScreenPositionToWorld(location.X, location.Y, WorldLocation, Direction);
		Direction *= 100.0f;
		WorldLocation += Direction;
		//I select the ARCorePLane that is more near to the point of my screen that I touched 
		float minDistance = 100000000000.0f;
		for (auto Tracked : Results)
		{
			float distance = UKismetMathLibrary::Vector_Distance(Tracked->GetLocalToWorldTransform().GetLocation()
				, WorldLocation);
			if (distance <= minDistance)
			{
				minDistance = distance;
				ARCorePlane = Tracked;
			}
		}
		
		planeTr = ARCorePlane->GetLocalToWorldTransform();
		TArray<AActor*> Actors;
		APawn* ARLevelP = ARLevelObj.Get();
		ARLevelP->GetAttachedActors(Actors, true, true);
		ARLevelP->SetActorScale3D(planeTr.GetScale3D() / 20.0f);
		ARLevelP->SetActorRotation(planeTr.GetRotation());
		//I adapt the height of level based on the distance between the AR camera and the ARCorePlane
		const float verticalDistance = (GetActorLocation() - planeTr.GetLocation()).Z;
		if (verticalDistance < 50.0f)
		{
			ARLevelP->SetActorLocation(planeTr.GetLocation());
		}
		else
		{
			float verticalDistancePercent = verticalDistance * 50.0f / 100.0f;
			ARLevelP->SetActorLocation(planeTr.GetLocation() + FVector(0.0f, 0.0f, verticalDistancePercent));
		}

		for (auto const child : Actors)
		{
			child->SetActorHiddenInGame(false);
		}
		
		const FVector SpawnLocation = ARLevelP->GetActorLocation();
		GetWorld()->SpawnActor(ARHero, &SpawnLocation);
		ARHeroObj = static_cast<AARHero*>(UGameplayStatics::GetActorOfClass(this, ARHero));
		ARHeroObj->LoadGame();
		
		for (auto waypoint : wayPoints)
		{
			static_cast<AARWaypoint*>(waypoint.Get())->SpawCharacter();
		}
		
		PlayerController->ActivateTouchInterface(TouchInterface);
		OnIsSpawned.Broadcast();
		bIsSpawned = true;
		ARHeroObj->OnCoinUpdate.Broadcast();
		ARHeroObj->OnLifeUpdate.Broadcast();
		ARHeroObj->OnSoulsUpdate.Broadcast();
		OnForwardMovement.AddDynamic(ARHeroObj, &AARHero::ForwardMovement);
		OnRightMovement.AddDynamic(ARHeroObj, &AARHero::RightMovement);
		OnJump.AddDynamic(ARHeroObj, &AARHero::JumpAction);
		OnAttack.AddDynamic(ARHeroObj, &AARHero::Attack);
		UGameplayStatics::PlaySound2D(GetWorld(), WorldSound);
		
	}
}

//Manage Hero movements
void AARManager::ForwardMovement(float inputValue)
{
	SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, GetActorRotation().Roll));
	OnForwardMovement.Broadcast(inputValue, GetActorForwardVector());
	
}

void AARManager::RightMovement(float inputValue)
{
	OnRightMovement.Broadcast(inputValue, GetActorRightVector());
}

void AARManager::JumpAction()
{
	OnJump.Broadcast();
}


void AARManager::AttackAction()
{
	OnAttack.Broadcast();
}


