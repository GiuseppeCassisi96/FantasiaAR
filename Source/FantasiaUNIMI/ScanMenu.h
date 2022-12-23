// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ARManager.h"
#include "Components/Button.h"
#include "ScanMenu.generated.h"

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
	virtual void NativeConstruct() override;
	UFUNCTION()
	void StartSession();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ARManager")
	TSubclassOf<AARManager> Manager;
};
