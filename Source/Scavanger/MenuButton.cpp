
#include "MenuButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMenuButton::NativeConstruct() {
	Super::NativeConstruct();

	if (Button) {
		Button->OnClicked.AddDynamic(this, &UMenuButton::OnClicked);
		Button->OnHovered.AddDynamic(this, &UMenuButton::OnHover);
		Button->OnUnhovered.AddDynamic(this, &UMenuButton::OnUnHover);
	}

	if (ButtonText) {
		ButtonText->SetText(ButtonLabel);
	}
}

void UMenuButton::OnClicked() {
	if (!LevelToLoadReference.IsNull()) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController) {
			// Set input mode to UI only
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoadReference);
	}

	if (bProgramQuit) {
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(GetWorld(),PlayerController, EQuitPreference::Quit, false);
		return;
	}
}

void UMenuButton::OnHover() {
	ButtonText->SetColorAndOpacity(FSlateColor(HoveredTextColor));
}


void UMenuButton::OnUnHover() {
	ButtonText->SetColorAndOpacity(FSlateColor(DefaultTextColor));
}

