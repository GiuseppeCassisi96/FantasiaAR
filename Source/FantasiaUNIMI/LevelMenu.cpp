// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMenu.h"

#include "Serialization/CompactBinary.h"

void UScanMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ScanButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::StartSession);
	PauseButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::PauseFunction);
	MenuButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::UScanMenu::GoToTheMenu);
	DialogueButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::UpdateDialogue);
}

void UScanMenu::StartSession()
{
	Manager = Cast<AARManager>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	Manager->OnScanIsComplete.AddDynamic(this, &UScanMenu::ScanIsCompleteEvent);
	Manager->OnIsSpawned.AddDynamic(this, &UScanMenu::IsSpawnedEvent);
	for (int i = 0; i < Manager->DialoguePoints.Num(); i++)
	{
		Cast<AARDialoguePoint>(Manager->DialoguePoints[i].Get())->StartDialogue.AddDynamic(this, &UScanMenu::OnStartDialogue);
		Cast<AARDialoguePoint>(Manager->DialoguePoints[i].Get())->EndDialogue.AddDynamic(this, &UScanMenu::OnEndDialogue);
	}
	UARBlueprintLibrary::StartARSession(Manager->ARSession);
	ScanButton->SetVisibility(ESlateVisibility::Hidden);
	Scanning->SetVisibility(ESlateVisibility::Visible);
}

void UScanMenu::ScanIsCompleteEvent()
{
	Scanning->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::IsSpawnedEvent()
{
	Coin->SetVisibility(ESlateVisibility::Visible);
	Heart->SetVisibility(ESlateVisibility::Visible);
	LifeText->SetVisibility(ESlateVisibility::Visible);
	CoinText->SetVisibility(ESlateVisibility::Visible);
	PauseButton->SetVisibility(ESlateVisibility::Visible);
	Manager->ARHeroObj->LifeUpdate.AddDynamic(this, &UScanMenu::UpdateHeroLifeUI);
	Manager->ARHeroObj->CoinUpdate.AddDynamic(this, &UScanMenu::UpdateHeroCoinUI);
}

void UScanMenu::UpdateHeroLifeUI()
{
	float HLife = Manager->ARHeroObj->heroLife;
	LifeText->SetText(FText::FromString(FString::FromInt(HLife)));
}

void UScanMenu::UpdateHeroCoinUI()
{
	float NCoin = Manager->ARHeroObj->numberOfCoin;
	CoinText->SetText(FText::FromString(FString::FromInt(NCoin)));
}

void UScanMenu::PauseFunction()
{
	bIsInPause = !bIsInPause;
	if(bIsInPause)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), bIsInPause);
		MenuButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), bIsInPause);
		MenuButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UScanMenu::GoToTheMenu()
{
	UARBlueprintLibrary::StopARSession();
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
}

void UScanMenu::OnStartDialogue(TArray<FString> dialogues, AActor* DialoguePoint)
{
	currentDialoguePoint = Cast<AARDialoguePoint>(DialoguePoint);
	if(!currentDialoguePoint->bDialogueIsComplete)
	{
		TextsDialogues = std::move(dialogues);
		DialogueBorder->SetVisibility(ESlateVisibility::Visible);
		DialogueText->SetVisibility(ESlateVisibility::Visible);
		DialogueText->SetText(FText::FromString(TextsDialogues[0]));
		if (TextsDialogues.Num() > 1)
		{
			DialogueButton->SetVisibility(ESlateVisibility::Visible);
		}
		currentDialoguePoint->dialogueIndex++;
		if (currentDialoguePoint->dialogueIndex == TextsDialogues.Num())
		{
			currentDialoguePoint->bDialogueIsComplete = true;
		}
	}
}

void UScanMenu::OnEndDialogue(AActor* DialoguePoint)
{
	DialogueBorder->SetVisibility(ESlateVisibility::Hidden);
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
	DialogueButton->SetVisibility(ESlateVisibility::Hidden);
	currentDialoguePoint->dialogueIndex = 0;
}

void UScanMenu::UpdateDialogue()
{
	if (currentDialoguePoint->dialogueIndex < TextsDialogues.Num())
	{
		DialogueText->SetText(FText::FromString(TextsDialogues[currentDialoguePoint->dialogueIndex]));
		currentDialoguePoint->dialogueIndex++;
		if(currentDialoguePoint->dialogueIndex == TextsDialogues.Num())
		{
			currentDialoguePoint->bDialogueIsComplete = true;
		}
	}
	
}




