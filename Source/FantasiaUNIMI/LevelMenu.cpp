// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMenu.h"

#include "Serialization/CompactBinary.h"

void UScanMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ScanButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::StartSession);
	PauseButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::PauseFunction);
	MenuButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::UScanMenu::GoToTheMenu);
	Manager = Cast<AARManager>(ManagerObjectPtr.Get());
	Manager->OnScanIsComplete.AddDynamic(this, &UScanMenu::ScanIsCompleteEvent);
	Manager->OnIsSpawned.AddDynamic(this, &UScanMenu::IsSpawnedEvent);
}

void UScanMenu::StartSession()
{
	UARBlueprintLibrary::StartARSession(Manager->ARSession);
	ScanButton->SetVisibility(ESlateVisibility::Hidden);
	Scanning->SetVisibility(ESlateVisibility::Visible);
}

void UScanMenu::ScanIsCompleteEvent()
{
	Scanning->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::IsSpawnedEvent()
{
	Coin->SetVisibility(ESlateVisibility::Visible);
	Heart->SetVisibility(ESlateVisibility::Visible);
	LifeText->SetVisibility(ESlateVisibility::Visible);
	CoinText->SetVisibility(ESlateVisibility::Visible);
	PauseButton->SetVisibility(ESlateVisibility::Visible);
	Manager->ARHeroObj->LifeUpdate.AddDynamic(this, &UScanMenu::UpdateHeroLifeUI);
	Manager->ARHeroObj->CoinUpdate.AddDynamic(this, &UScanMenu::UpdateHeroCoinUI);
}

void UScanMenu::UpdateHeroLifeUI()
{
	float HLife = Manager->ARHeroObj->heroLife;
	LifeText->SetText(FText::FromString(FString::FromInt(HLife)));
}

void UScanMenu::UpdateHeroCoinUI()
{
	float NCoin = Manager->ARHeroObj->numberOfCoin;
	CoinText->SetText(FText::FromString(FString::FromInt(NCoin)));
}

void UScanMenu::PauseFunction()
{
	bIsInPause = !bIsInPause;
	if(bIsInPause)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), bIsInPause);
		MenuButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), bIsInPause);
		MenuButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UScanMenu::GoToTheMenu()
{
	UARBlueprintLibrary::StopARSession();
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
}



