// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShootAttack.h"
#include "IDamageable.h"

// Sets default values for this component's properties
UBaseShootAttack::UBaseShootAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseShootAttack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseShootAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseShootAttack::BaseShootAttack()
{
	UWorld* world = GetWorld();
	FHitResult hitResult;
	AActor* player = GetOwner();
	
	APawn* pawn = Cast<APawn>(player);	
	if (!pawn)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(pawn->GetController());	
	if (!PlayerController)
	{
		return;
	}
	
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	FVector start = player->GetActorLocation() + player->GetActorForwardVector() * offset;
	FVector end = start + player->GetActorForwardVector() * range;
	
	DrawDebugLine(world, start, end, FColor(255, 0, 0), false, 5.f);

	if (world->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility))
	{
		UObject* HitObject = hitResult.GetActor();
		if (HitObject)
		{
			IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject);
			if (DamageableActor)
			{
				DamageableActor->TakeDamage(damage);
			}
		}
	}
}

