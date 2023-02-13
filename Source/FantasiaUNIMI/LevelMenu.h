// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "ARManager.h"
#include "SavePoint.h"
#include "ARDialoguePoint.h"
#include "ARDeathCollider.h"
#include "ARChangeLevel.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
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
	UButton* ChangeLevelButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* AButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PauseButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DialogueButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UBorder* DialogueBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* ChangeLevelBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* DeathBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MenuButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LifeText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DeathText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TouchText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DialogueText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GameOverText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ChangeLevelText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoinText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SaveText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* Scanning;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Coin;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Heart;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Souls;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SoulText;
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TSoftObjectPtr<UWorld> MenuLevel;
	UPROPERTY(EditDefaultsOnly, Category="DeathColliderClass")
	TSubclassOf<AActor> DeathColliderClass;
	UPROPERTY()
	AARDeathCollider* DeathCollider;
	UPROPERTY(EditDefaultsOnly, Category = "ChangeLevelClass")
	TSubclassOf<AActor> ChangeLevelClass;
	UPROPERTY()
	AARChangeLevel* ChangeLevel;
	UPROPERTY()
	AARManager* Manager;
	UPROPERTY()
	AARDialoguePoint* currentDialoguePoint;
	bool bIsInPause;
	TArray<FString> TextsDialogues;
	FTimerDelegate deathTimerDelegate;
	FTimerHandle deathTimer;
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
	void UpdateHeroSoulsUI();
	UFUNCTION()
	void PauseFunction();

	UFUNCTION()
	void GoToTheMenu();

	UFUNCTION()
	void OnStartDialogue(TArray<FString> dialogues,  AActor* DialoguePoint);
	UFUNCTION()
	void OnEndDialogue(AActor* DialoguePoint);
	UFUNCTION()
	void UpdateDialogue();
	UFUNCTION()
	void VisibleSaveText();
	UFUNCTION()
	void HiddenSaveText();
	UFUNCTION()
	void LoseOneSoulEvent();
	UFUNCTION()
	void HideDeathText();
	UFUNCTION()
	void GameOverEvent();
	UFUNCTION()
	void ChangeLevelEvent();
	UFUNCTION()
	void GoToTheNextLevel();

	
};
