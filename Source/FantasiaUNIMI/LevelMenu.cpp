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
	ExitButton->OnClicked.AddDynamic(this, &UScanMenu::GoToTheMenu);
	ChangeLevelButton->OnClicked.AddDynamic(this, &UScanMenu::GoToTheNextLevel);

	DeathCollider = Cast<AARDeathCollider>(UGameplayStatics::GetActorOfClass(GetWorld(), 
		DeathColliderClass));
	ChangeLevel = Cast<AARChangeLevel>(UGameplayStatics::GetActorOfClass(GetWorld(),
		ChangeLevelClass));
	
}

void UScanMenu::StartSession()
{
	Manager = Cast<AARManager>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	Manager->OnScanIsComplete.AddDynamic(this, &UScanMenu::ScanIsComplete);
	Manager->OnIsSpawned.AddDynamic(this, &UScanMenu::IsSpawned);
	for (int i = 0; i < Manager->DialoguePoints.Num(); i++)
	{
		Cast<AARDialoguePoint>(Manager->DialoguePoints[i].Get())->OnStartDialogue.AddDynamic(this, &UScanMenu::StartDialogue);
		Cast<AARDialoguePoint>(Manager->DialoguePoints[i].Get())->OnEndDialogue.AddDynamic(this, &UScanMenu::EndDialogue);
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

void UScanMenu::ScanIsComplete()
{
	Scanning->SetVisibility(ESlateVisibility::Hidden);
	TouchText->SetVisibility(ESlateVisibility::Visible);

	DeathCollider->OnLoseOneSoul.AddDynamic(this, &UScanMenu::LoseOneSoul);
	deathTimerDelegate.BindUFunction(this, "HideDeathText");
	DeathCollider->OnGameOver.AddDynamic(this, &UScanMenu::GameOver);
	ChangeLevel->OnNextLevelUI.AddDynamic(this, &UScanMenu::NextLevelUI);
	ChangeLevel->OnEndNextLevelUI.AddDynamic(this, &UScanMenu::UScanMenu::EndNextLevelUI);
}

void UScanMenu::IsSpawned()
{
	TouchText->SetVisibility(ESlateVisibility::Hidden);
	Coin->SetVisibility(ESlateVisibility::Visible);
	Souls->SetVisibility(ESlateVisibility::Visible);
	Heart->SetVisibility(ESlateVisibility::Visible);
	LifeText->SetVisibility(ESlateVisibility::Visible);
	CoinText->SetVisibility(ESlateVisibility::Visible);
	SoulText->SetVisibility(ESlateVisibility::Visible);
	PauseButton->SetVisibility(ESlateVisibility::Visible);
	JumpButton->SetVisibility(ESlateVisibility::Visible);
	AttackButton->SetVisibility(ESlateVisibility::Visible);

	JumpButton->OnPressed.AddDynamic(Manager, &AARManager::JumpAction);
	AttackButton->OnPressed.AddDynamic(Manager, &AARManager::AttackAction);
	Manager->ARHeroObj->OnLifeUpdate.AddDynamic(this, &UScanMenu::UpdateLife);
	Manager->ARHeroObj->OnCoinUpdate.AddDynamic(this, &UScanMenu::UpdateCoin);
	Manager->ARHeroObj->OnSoulsUpdate.AddDynamic(this, &UScanMenu::UpdateSouls);
	Manager->ARHeroObj->OnDeathEvent.AddDynamic(this, &UScanMenu::GameOver);
	
}

void UScanMenu::UpdateLife()
{
	float HLife = Manager->ARHeroObj->heroLife;
	LifeText->SetText(FText::FromString(FString::FromInt(HLife)));
}

void UScanMenu::UpdateCoin()
{
	float NCoin = Manager->ARHeroObj->numberOfCoin;
	CoinText->SetText(FText::FromString(FString::FromInt(NCoin)));
}

void UScanMenu::UpdateSouls()
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
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
	UARBlueprintLibrary::StopARSession();
}

void UScanMenu::StartDialogue(TArray<FString> dialogues, AActor* DialoguePoint)
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

void UScanMenu::EndDialogue(AActor* DialoguePoint)
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

void UScanMenu::LoseOneSoul()
{
	DeathText->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(deathTimer, deathTimerDelegate, 5.0f, false);
}

void UScanMenu::HideDeathText()
{
	DeathText->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::GameOver()
{
	DeathBorder->SetVisibility(ESlateVisibility::Visible);
	GameOverText->SetVisibility(ESlateVisibility::Visible);
	ExitButton->SetVisibility(ESlateVisibility::Visible);
	DeathText->SetVisibility(ESlateVisibility::Hidden);
	
}

void UScanMenu::NextLevelUI(FString Text)
{
	ChangeLevelBorder->SetVisibility(ESlateVisibility::Visible);
	ChangeLevelButton->SetVisibility(ESlateVisibility::Visible);
	ChangeLevelText->SetVisibility(ESlateVisibility::Visible);
	ChangeLevelText->SetText(FText::FromString(Text));
	
}

void UScanMenu::EndNextLevelUI(FString Text)
{
	ChangeLevelBorder->SetVisibility(ESlateVisibility::Hidden);
	ChangeLevelButton->SetVisibility(ESlateVisibility::Hidden);
	ChangeLevelText->SetVisibility(ESlateVisibility::Hidden);
}

void UScanMenu::GoToTheNextLevel()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), ChangeLevel->NextLevel);
	UARBlueprintLibrary::StopARSession();
}




