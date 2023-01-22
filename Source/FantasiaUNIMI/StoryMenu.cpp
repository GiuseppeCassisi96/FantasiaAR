 // Fill out your copyright notice in the Description page of Project Settings.


#include "StoryMenu.h"

#include "Kismet/GameplayStatics.h"

 void UStoryMenu::NativeConstruct()
{
	Super::NativeConstruct();
	NextButton->OnPressed.AddDynamic(this, &UStoryMenu::InitStory);
}

 void UStoryMenu::InitStory()
 {
	 UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), FirstLevel);
 }
