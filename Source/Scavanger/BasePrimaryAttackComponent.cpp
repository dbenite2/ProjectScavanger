// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePrimaryAttackComponent.h"

#include "IDamageable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBasePrimaryAttackComponent::UBasePrimaryAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBasePrimaryAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBasePrimaryAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBasePrimaryAttackComponent::BasePrimaryAttack()
{
	UWorld* world = GetWorld();
	float sphereRadius = 300.0f;
	TArray<AActor*> overlappingActors;
	AActor* player = GetOwner();
	FVector playerLocation = player->GetActorLocation();

	UKismetSystemLibrary::SphereOverlapActors(
		world,
		playerLocation,
		sphereRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>(),
		nullptr,
		TArray<AActor*>(),
		overlappingActors
	);

	for(AActor* Actor : overlappingActors)
	{
		DrawDebugSphere(world, playerLocation, sphereRadius, 12, FColor::Red, false, 5.0f, 0, 1.0f);

		if(Actor)
		{
			IIDamageable* damageableActor = Cast<IIDamageable>(Actor);

			if(damageableActor)
			{
				damageableActor->TakeDamage(50.0f);
			}
		}
	}
}

