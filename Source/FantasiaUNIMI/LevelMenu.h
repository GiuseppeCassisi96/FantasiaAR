// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ARManager.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "LevelMenu.generated.h"

/**
 * 
 */


UCLASS()
class FANTASIAUNIMI_API UScanMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ScanButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PauseButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MenuButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LifeText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoinText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* Scanning;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Coin;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Heart;

	UPROPERTY(EditDefaultsOnly, Category = "ARManager")
	TSoftObjectPtr<APawn> ManagerObjectPtr;
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TSoftObjectPtr<UWorld> MenuLevel;
	UPROPERTY()
	AARManager* Manager;
	bool bIsInPause;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void StartSession();

	UFUNCTION()
	void ScanIsCompleteEvent();
	UFUNCTION()
	void IsSpawnedEvent();
	UFUNCTION()
	void UpdateHeroLifeUI();
	UFUNCTION()
	void UpdateHeroCoinUI();
	UFUNCTION()
	void PauseFunction();

	UFUNCTION()
	void GoToTheMenu();
	
};
