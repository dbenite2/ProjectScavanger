#include "LioraKadeController.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerUI.h"
#include "PauseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ALioraKadeController::BeginPlay() {
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	if (!PlayerWidgetTemplate) return;
	PlayerWidget = CreateWidget<UPlayerUI>(this, PlayerWidgetTemplate);
	if (PlayerWidget) {
		PlayerWidget->AddToViewport(0);
	}
	
	
	if (!PauseMenuTemplate) return;
	PauseMenuWidget = CreateWidget<UPauseMenu>(this, PauseMenuTemplate);
	if (PauseMenuWidget) {
		PauseMenuWidget->AddToViewport(1);
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ALioraKadeController::ShowPauseMenu() {
	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}

void ALioraKadeController::UnPauseGame() {
	bShowMouseCursor = false;
	PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	SetInputMode(FInputModeGameOnly());
}


