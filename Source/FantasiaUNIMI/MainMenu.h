// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class FANTASIAUNIMI_API UMainMenu : public UUserWidget
{

	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* PlayButton;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* TutorialButton;
	UPROPERTY(EditDefaultsOnly, Category="Levels")
	TSoftObjectPtr<UWorld> Tutorial;
	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> Story;
	UFUNCTION()
	void StartsTutorial();
	UFUNCTION()
	void StartsStory();

	
};
