// Fill out your copyright notice in the Description page of Project Settings.


#include "LioraKadeController.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerUI.h"
#include "Blueprint/UserWidget.h"

void ALioraKadeController::BeginPlay() {
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	if (PlayerWidgetTemplate) {
		PlayerWidget = CreateWidget<UPlayerUI>(this, PlayerWidgetTemplate);
		if (PlayerWidget) {
			PlayerWidget->AddToViewport(0);
		}
	}
}
