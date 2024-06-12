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
	world = GetWorld();

	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null!"));
		return;
	}

	player = GetOwner();
	if (!player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is null!"));
		return;
	}

	APawn* pawn = Cast<APawn>(player);
	if (!pawn)
	{
		return;
	}
	
	AController* Controller = pawn->GetController();

	APlayerController* PlayerController = Cast<APlayerController>(pawn->GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null!"));
		return;
	}

	if (!PlayerController->PlayerCameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCameraManager is null!"));
		return;
	}
	
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	start = player->GetActorLocation() + player->GetActorForwardVector() * offset;
	end = start + SpawnRotation.Vector() * range;

	FHitResult HitResult;
	
	DrawDebugLine(world, start, end, FColor(255, 0, 0), true);

	if (world->LineTraceSingleByChannel(HitResult, start, end, ECC_Visibility))
	{
		UObject* HitObject = HitResult.GetActor();
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

