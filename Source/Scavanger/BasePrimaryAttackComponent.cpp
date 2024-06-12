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
	world = GetWorld();
	sphereRadius = 70.0f;
	sphereHalfHeightRadius = 5.0f;
	player = GetOwner();
	forwardOffset = {60.f, 60.f, 0};
	FVector playerLocation = player->GetActorLocation() + player->GetActorForwardVector() * forwardOffset;

	UKismetSystemLibrary::CapsuleOverlapActors(
		world,
		playerLocation,
		sphereRadius,
		sphereHalfHeightRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>(),
		nullptr,
		TArray<AActor*>(),
		overlappingActors
	);
	// DrawDebugSphere(world, playerLocation, sphereRadius, 12, FColor::Red, false, 5.0f, 0, 1.0f);

	DrawDebugCapsule(
		world,
		playerLocation,
		sphereHalfHeightRadius,
		sphereRadius,
		FQuat::Identity,
		FColor::Red,
		false, // true si deseas que la cápsula se dibuje persistentemente
		5.0f, // Duración que la cápsula se mantendrá dibujada (5 segundos en este caso)
		0,
		2.0f // Grosor de la línea
	);

	for(AActor* Actor : overlappingActors)
	{
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

