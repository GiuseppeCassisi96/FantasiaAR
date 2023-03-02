// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class FANTASIAUNIMI_API UStoryMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	 * @brief Button that loads the level1 level
	 */
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* StartsButton;
	/**
	 * @brief Button that replaces the old text with the new text. The new text will be got from 'ArrayOfText'
	 */
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* ContinueButton;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* StoryText;
	/**
	 * @brief A reference to the first level 
	 */
	UPROPERTY(EditDefaultsOnly, Category="Level")
	TSoftObjectPtr<UWorld> FirstLevel;
	/**
	 * @brief Array that contains texts 
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Text")
	TArray<FString> ArrayOfText;
	int index;
	virtual void NativeConstruct() override;
	/**
	 * @brief Function that saves the first data and loads the first level
	 */
	UFUNCTION()
	void InitStory();
	/**
	 * @brief Set the text block with the new text
	 */
	UFUNCTION()
	void ViewNewText();
	
};
