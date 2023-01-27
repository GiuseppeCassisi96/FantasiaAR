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
	int xSize, ySize;
	PlayerController->GetViewportSize(xSize, ySize);
	ScreenSize.X = static_cast<float>(xSize);
	ScreenSize.Y = static_cast<float>(ySize);
	ScreenSize *= 0.5f;
	bScanIsComplete = false;
	bIsSpawned = false;
	bIsTracked = false;
	UARBlueprintLibrary::StopARSession();
}

// Called every frame
void AARManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bScanIsComplete)
	{
		Results = UARBlueprintLibrary::GetAllGeometries();
		if (Results.Num() > 0)
		{
			ARCorePlane = Results[0];
			planeTr = ARCorePlane->GetLocalToWorldTransform();
			bScanIsComplete = true;
			OnScanIsComplete.Broadcast();
		}
	}
	else
	{
		UARBlueprintLibrary::DebugDrawTrackedGeometry(ARCorePlane, this,
			FColor::Red);
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
	if (ARCorePlane != nullptr && !bIsSpawned)
	{
		TArray<AActor*> Actors;
		ARLevelObj.Get()->GetAttachedActors(Actors, true, true);
		for (auto const child : Actors)
		{
			child->SetActorHiddenInGame(false);
		}
		FVector distance = GetActorLocation() - planeTr.GetLocation();
		if(distance.Z < 40.0f)
		{
			ARLevelObj.Get()->SetActorLocation(planeTr.GetLocation());
		}
		else
		{
			ARLevelObj.Get()->SetActorLocation(planeTr.GetLocation() + FVector(0.0f, 0.0f, 50.0f));
		}
		ARLevelObj.Get()->SetActorRotation(planeTr.GetRotation());
		const FVector SpawnLocation = ARLevelObj.Get()->GetActorLocation();
		GetWorld()->SpawnActor(ARHero, &SpawnLocation);
		ARHeroObj = static_cast<AARHero*>(UGameplayStatics::GetActorOfClass(this, ARHero));
		ARHeroObj->LoadGame();
		bIsSpawned = true;
		for (auto waypoint : wayPoints)
		{
			static_cast<AARWaypoint*>(waypoint.Get())->SpawCharacter();
		}
		PlayerController->ActivateTouchInterface(TouchInterface);
		OnIsSpawned.Broadcast();
		ARHeroObj->CoinUpdate.Broadcast();
		ARHeroObj->LifeUpdate.Broadcast();
		ARHeroObj->SoulsUpdate.Broadcast();
		OnForwardMovement.AddDynamic(ARHeroObj, &AARHero::ForwardMovement);
		OnRightMovement.AddDynamic(ARHeroObj, &AARHero::RightMovement);
		OnJump.AddDynamic(ARHeroObj, &AARHero::JumpAction);
		OnAttack.AddDynamic(ARHeroObj, &AARHero::Attack);
		
	}

}

//Manage Hero movements
void AARManager::ForwardMovement(float inputValue)
{
	OnForwardMovement.Broadcast(inputValue, GetTransform().GetUnitAxis(EAxis::Type::X));
}

void AARManager::RightMovement(float inputValue)
{
	OnRightMovement.Broadcast(inputValue, GetTransform().GetUnitAxis(EAxis::Type::Y));
}

void AARManager::JumpAction()
{
	OnJump.Broadcast();
}


void AARManager::AttackAction()
{
	OnAttack.Broadcast();
}


