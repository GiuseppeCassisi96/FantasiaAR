// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	TutorialButton->OnPressed.AddDynamic(this, &UMainMenu::StartsTutorial);
	PlayButton->OnPressed.AddDynamic(this, &UMainMenu::StartsStory);
}

void UMainMenu::StartsTutorial()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Tutorial);
}

void UMainMenu::StartsStory()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Story);
}
