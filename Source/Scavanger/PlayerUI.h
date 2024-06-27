#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

class UImage;

UCLASS()
class SCAVANGER_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* GreenHealthBar{nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* RedHealthBar{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* BackgroundHealthBar{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* CurrentWeapon{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* BulletType{nullptr};

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Options")
	TArray<UImage*> WeaponIcons;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Options")
	TArray<UImage*> BulletIcons;

	UFUNCTION()
	void OnHealthChange(const int Current, const int Max);

	UFUNCTION()
	void OnWeaponChange();

	UFUNCTION()
	void OnBulletChange();
};
