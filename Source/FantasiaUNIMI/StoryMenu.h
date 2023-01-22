// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class FANTASIAUNIMI_API UStoryMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* NextButton;
	UPROPERTY(EditDefaultsOnly, Category="Level")
	TSoftObjectPtr<UWorld> FirstLevel;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void InitStory();
	
};
