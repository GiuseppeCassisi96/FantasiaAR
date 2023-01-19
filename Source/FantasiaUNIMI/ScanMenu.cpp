// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanMenu.h"
void UScanMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ScanButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::StartSession);
	Manager = Cast<AARManager>(ManagerObjectPtr.Get());
}

void UScanMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Manager->bScanIsComplete)
	{
		Scanning->SetVisibility(ESlateVisibility::Hidden);
		if(Manager->bIsSpawned && Manager->ARHeroObj != nullptr)
		{
			Coin->SetVisibility(ESlateVisibility::Visible);
			Heart->SetVisibility(ESlateVisibility::Visible);
			LifeText->SetVisibility(ESlateVisibility::Visible);
			CoinText->SetVisibility(ESlateVisibility::Visible);
			float HLife = Manager->ARHeroObj->heroLife;
			float NCoin = Manager->ARHeroObj->numberOfCoin;
			LifeText->SetText(FText::FromString(FString::FromInt(HLife)));
			CoinText->SetText(FText::FromString(FString::FromInt(NCoin)));
		}
	}
}

void UScanMenu::StartSession()
{
	UARBlueprintLibrary::StartARSession(Manager->ARSession);
	ScanButton->SetVisibility(ESlateVisibility::Hidden);
	Scanning->SetVisibility(ESlateVisibility::Visible);
}

