#include "Life_Component.h"

ULife_Component::ULife_Component() {
	PrimaryComponentTick.bCanEverTick = true;
}

void ULife_Component::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void ULife_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void ULife_Component::ModifyHealth(float Amount) {
	CurrentHealth -= Amount;

	if (CurrentHealth > 0) {
		OnLifeChange.Broadcast(CurrentHealth, MaxHealth);
		return;
	}

	if(CurrentHealth <= 0)
	{
		ActorDie();
	}
}

void ULife_Component::ActorDie()
{
	CurrentHealth = 0;
	GetOwner()->Destroy();
}

