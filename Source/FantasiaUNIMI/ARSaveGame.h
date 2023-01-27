// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ARSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category="SaveGameData")
	int life;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int coin;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int souls;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	UWorld* LevelToLoad;
};
UCLASS()
class FANTASIAUNIMI_API UARSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UARSaveGame();
	UPROPERTY(VisibleAnywhere, Category=basic)
	FString UserName;
	UPROPERTY(VisibleAnywhere, Category = basic)
	int UserIndex;
	UPROPERTY(VisibleAnywhere, Category = basic)
	FCharacterData CharacterData;
	
};
