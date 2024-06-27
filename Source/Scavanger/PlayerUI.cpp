#include "PlayerUI.h"

#include "Life_Component.h"
#include "LioraKade.h"
#include "Components/Image.h"

void UPlayerUI::NativeConstruct() {
	Super::NativeConstruct();

	const auto* World = GetWorld();
	if (!World) return;
	const APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller) return;
	const ALioraKade* Player = Cast<ALioraKade>(Controller->GetPawn());
	if (!Player || !Player->LifeComponent) return;
	Player->LifeComponent->OnLifeChange.AddDynamic(this, &UPlayerUI::OnHealthChange);
}

void UPlayerUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	const double CurrentScale = RedHealthBar->GetRenderTransform().Scale.X;
	const double TriggerScale = GreenHealthBar->GetRenderTransform().Scale.X;

	double const Lerp = FMath::Lerp(CurrentScale, TriggerScale, InDeltaTime * 3.f);
	RedHealthBar->SetRenderScale({Lerp, 1});
}


void UPlayerUI::OnHealthChange(const int Current, const int Max) {
	GreenHealthBar->SetRenderScale({(float)Current / float(Max), 1});
}

void UPlayerUI::OnBulletChange() {
	// change bullet icon in widget
}

void UPlayerUI::OnWeaponChange() {
	// change weapon icon in widget 
}



