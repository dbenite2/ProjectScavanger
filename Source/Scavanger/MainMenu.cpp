// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct() {
	Super::NativeConstruct();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// Set input mode to UI only
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}
