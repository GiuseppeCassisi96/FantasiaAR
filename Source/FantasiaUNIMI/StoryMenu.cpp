 // Fill out your copyright notice in the Description page of Project Settings.


#include "StoryMenu.h"

#include "ARSaveGame.h"
#include "Kismet/GameplayStatics.h"

 void UStoryMenu::NativeConstruct()
{
	Super::NativeConstruct();
	NextButton->OnPressed.AddDynamic(this, &UStoryMenu::InitStory);
	ContinueButton->OnPressed.AddDynamic(this, &UStoryMenu::ViewNewText);
	StoryText->SetText(FText::FromString(ArrayOfText[0]));
}

 void UStoryMenu::InitStory()
 {
	 UARSaveGame* SaveGameInstance = Cast<UARSaveGame>(UGameplayStatics::CreateSaveGameObject(
		 UARSaveGame::StaticClass()));
	 SaveGameInstance->CharacterData.life = 100;
	 SaveGameInstance->CharacterData.coin = 0;
	 SaveGameInstance->CharacterData.souls = 3;
	 SaveGameInstance->CharacterData.LevelToLoad = FirstLevel.Get();
	 UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->UserName,
		 SaveGameInstance->UserIndex);
	 UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), FirstLevel);
 }

 void UStoryMenu::ViewNewText()
 {
	 if(index < ArrayOfText.Num())
	 {
		 StoryText->SetText(FText::FromString(ArrayOfText[index]));
		 index++;
		if(index >= ArrayOfText.Num())
		{
			ContinueButton->SetVisibility(ESlateVisibility::Hidden);
		}
	 }
 }
