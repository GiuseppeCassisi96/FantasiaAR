// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	TutorialButton->OnPressed.AddDynamic(this, &UMainMenu::StartsTutorial);
	PlayButton->OnPressed.AddDynamic(this, &UMainMenu::StartsStory);
	LoadButton->OnPressed.AddDynamic(this, &UMainMenu::LoadLevel);
}

void UMainMenu::StartsTutorial()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Tutorial);
}

void UMainMenu::StartsStory()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Story);
}

void UMainMenu::LoadLevel()
{
	UARSaveGame* LoadSaveGameInstance = Cast<UARSaveGame>( UGameplayStatics::CreateSaveGameObject(UARSaveGame::StaticClass()));
	LoadSaveGameInstance = Cast<UARSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadSaveGameInstance->UserName, LoadSaveGameInstance->UserIndex));
	if(LoadSaveGameInstance == nullptr)
		return;
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LoadSaveGameInstance->CharacterData.LevelToLoad);
}
