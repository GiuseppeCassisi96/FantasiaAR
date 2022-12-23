// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanMenu.h"
void UScanMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ScanButton->OnClicked.AddUniqueDynamic(this, &UScanMenu::StartSession);
}

void UScanMenu::StartSession()
{
	UARBlueprintLibrary::StartARSession(Manager.GetDefaultObject()->ARSession);
}
