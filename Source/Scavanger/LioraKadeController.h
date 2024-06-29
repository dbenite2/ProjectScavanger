#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LioraKadeController.generated.h"

class UPauseMenu;
class UPlayerUI;
class UInputMappingContext;

UCLASS()
class SCAVANGER_API ALioraKadeController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	bool bShowPauseMenu{false};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerUI> PlayerWidgetTemplate{nullptr};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPauseMenu> PauseMenuTemplate{nullptr};
	
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	UPlayerUI* PlayerWidget{nullptr};

	UPROPERTY()
	UPauseMenu* PauseMenuWidget{nullptr};

	UFUNCTION()
	void UnPauseGame();
	
	UFUNCTION()
	void ShowPauseMenu();
};
