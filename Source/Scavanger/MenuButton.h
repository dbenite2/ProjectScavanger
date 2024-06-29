// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuButton.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class SCAVANGER_API UMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button{nullptr};

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText{nullptr};

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClicked();

	UFUNCTION()
	void OnHover();

	UFUNCTION()
	void OnUnHover();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	TSoftObjectPtr<UWorld> LevelToLoadReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	bool bProgramQuit{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	bool bResumeGame{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FText ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FLinearColor DefaultTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FLinearColor HoveredTextColor;
};
