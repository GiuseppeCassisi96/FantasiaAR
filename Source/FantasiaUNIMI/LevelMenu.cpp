// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMenu.h"

#include "Serialization/CompactBinary.h"

void UScanMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ScanButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::StartSession);
	PauseButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::PauseFunction);
	MenuButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::GoToTheMenu);
	DialogueButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::UpdateDialogue);
	DeathCollider = Cast<AARDeathCollider>(UGameplayStatics::GetActorOfClass(GetWorld(), 
		DeathColliderClass));
	ChangeLevel = Cast<AARChangeLevel>(UGameplayStatics::GetActorOfClass(GetWorld(),
		ChangeLevelClass));
	ExitButton->OnClicked.AddDynamic(this, &UScanMenu::GoToTheMenu);
	ChangeLevelButton->OnClicked.AddDynamic(this, &UScanMenu::GoToTheNextLevel);
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
	if(Manager->SavePoint != nullptr)
	{
		Cast<ASavePoint>(Manager->SavePoint.Get())->OnVisibleSaveText.AddDynamic(this, &UScanMenu::VisibleSaveText);
		Cast<ASavePoint>(Manager->SavePoint.Get())->OnHiddenSaveText.AddDynamic(this, &UScanMenu::HiddenSaveText);
	}
	UARBlueprintLibrary::StartARSession(Manager->ARSession);
	ScanButton->SetVisibility(ESlateVisibility::Hidden);
	Scanning->SetVisibility(ESlateVisibility::Visible);
}

void UScanMenu::ScanIsCompleteEvent()
{
	Scanning->SetVisibility(ESlateVisibility::Hidden);
	TouchText->SetVisibility(ESlateVisibility::Visible);
	DeathCollider->LoseOneSoulEvent.AddDynamic(this, &UScanMenu::LoseOneSoulEvent);
	deathTimerDelegate.BindUFunction(this, "HideDeathText");
	DeathCollider->GameOverEvent.AddDynamic(this, &UScanMenu::GameOverEvent);
	ChangeLevel->ChangeLevelEvent.AddDynamic(this, &UScanMenu::ChangeLevelEvent);
}

void UScanMenu::IsSpawnedEvent()
{
	TouchText->SetVisibility(ESlateVisibility::Hidden);
	Coin->SetVisibility(ESlateVisibility::Visible);
	Souls->SetVisibility(ESlateVisibility::Visible);
	Heart->SetVisibility(ESlateVisibility::Visible);
	LifeText->SetVisibility(ESlateVisibility::Visible);
	CoinText->SetVisibility(ESlateVisibility::Visible);
	SoulText->SetVisibility(ESlateVisibility::Visible);
	PauseButton->SetVisibility(ESlateVisibility::Visible);
	AButton->SetVisibility(ESlateVisibility::Visible);
	BButton->SetVisibility(ESlateVisibility::Visible);
	AButton->OnPressed.AddDynamic(Manager, &AARManager::JumpAction);
	BButton->OnPressed.AddDynamic(Manager, &AARManager::AttackAction);
	Manager->ARHeroObj->LifeUpdate.AddDynamic(this, &UScanMenu::UpdateHeroLifeUI);
	Manager->ARHeroObj->CoinUpdate.AddDynamic(this, &UScanMenu::UpdateHeroCoinUI);
	Manager->ARHeroObj->SoulsUpdate.AddDynamic(this, &UScanMenu::UpdateHeroSoulsUI);
	
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

void UScanMenu::UpdateHeroSoulsUI()
{
	float HSouls = Manager->ARHeroObj->heroSouls;
	SoulText->SetText(FText::FromString(FString::FromInt(HSouls)));
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
	currentDialoguePoint->bDialogueIsComplete = false;
}

void UScanMenu::UpdateDialogue()
{
	if (currentDialoguePoint->dialogueIndex < TextsDialogues.Num())
	{
		DialogueText->SetText(FText::FromString(TextsDialogues[currentDialoguePoint->dialogueIndex]));
		currentDialoguePoint->dialogueIndex++;
		if(currentDialoguePoint->dialogueIndex == TextsDialogues.Num())
		{
			DialogueButton->SetVisibility(ESlateVisibility::Hidden);
			currentDialoguePoint->bDialogueIsComplete = true;
		}
	}
	
}

void UScanMenu::VisibleSaveText()
{
	SaveText->SetVisibility(ESlateVisibility::Visible);
}

void UScanMenu::HiddenSaveText()
{
	SaveText->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::LoseOneSoulEvent()
{
	DeathText->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(deathTimer, deathTimerDelegate, 5.0f, false);
}

void UScanMenu::HideDeathText()
{
	DeathText->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::GameOverEvent()
{
	DeathBorder->SetVisibility(ESlateVisibility::Visible);
	GameOverText->SetVisibility(ESlateVisibility::Visible);
	ExitButton->SetVisibility(ESlateVisibility::Visible);
	DeathText->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::ChangeLevelEvent()
{
	ChangeLevelBorder->SetVisibility(ESlateVisibility::Visible);
	ChangeLevelButton->SetVisibility(ESlateVisibility::Visible);
	ChangeLevelText->SetVisibility(ESlateVisibility::Visible);
}

void UScanMenu::GoToTheNextLevel()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), ChangeLevel->NextLevel);
}




