#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LioraKadeController.generated.h"

class UPlayerUI;
class UInputMappingContext;

UCLASS()
class SCAVANGER_API ALioraKadeController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerUI> PlayerWidgetTemplate{nullptr};

	virtual void BeginPlay() override;

public:

	UPROPERTY()
	UPlayerUI* PlayerWidget{nullptr};
};
