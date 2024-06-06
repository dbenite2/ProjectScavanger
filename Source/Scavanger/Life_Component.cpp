// Fill out your copyright notice in the Description page of Project Settings.


#include "Life_Component.h"

// Sets default values for this component's properties
ULife_Component::ULife_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	maxHealth = 100.0f;
	currentHealth = maxHealth;
}


// Called when the game starts
void ULife_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULife_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULife_Component::ModifyHealth(float amount)
{
	currentHealth -= amount;

	if(currentHealth <= 0)
	{
		ActorDie();
	}
}

void ULife_Component::ActorDie()
{
	currentHealth = 0;
	GetOwner()->Destroy();
}

