#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UMenuButton;

UCLASS()
class SCAVANGER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Game menu system")
	UMenuButton* NewGameButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Game menu system")
	UMenuButton* OptionsButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Game menu system")
	UMenuButton* QuitButton{nullptr};
	
};
