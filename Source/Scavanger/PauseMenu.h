#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UVerticalBox;
class UMenuButton;

UCLASS()
class SCAVANGER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UMenuButton* ContinueButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UMenuButton* MainMenuButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UMenuButton* QuitButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UVerticalBox* ButtonContainer{nullptr};
};
