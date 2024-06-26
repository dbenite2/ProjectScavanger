#include "ZeroGravityComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UZeroGravityComponent::UZeroGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UZeroGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);

	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner())) {
		CharacterMovement = OwnerCharacter->GetCharacterMovement();
	}	
}


// Called every frame
void UZeroGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CharacterMovement) {
		// Manually counteract the gravity for characters
		FVector AntiGravity = FVector(0.f, 0.f, -GetWorld()->GetGravityZ()) * DeltaTime;
		CharacterMovement->Velocity += AntiGravity;
	} else if (AActor* Owner = GetOwner()) {
		// Manually counteract the gravity for other actors
		FVector CurrentLocation = Owner->GetActorLocation();
		FVector AntiGravity = FVector(0.f, 0.f, GetWorld()->GetGravityZ()) * DeltaTime;
		FVector NewLocation = CurrentLocation - AntiGravity;

		Owner->SetActorLocation(NewLocation, true);
	}
}

void UZeroGravityComponent::ActivateZeroGravity(float Duration) {
	SetComponentTickEnabled(true);

	if (CharacterMovement) {
		CharacterMovement->GravityScale = MinGravityValue;
	}
	
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(ZeroGravityTimerHandle, this, &UZeroGravityComponent::DeactivateZeroGravity, Duration, false);
}

void UZeroGravityComponent::DeactivateZeroGravity() {
	if (CharacterMovement) {
		CharacterMovement->GravityScale = 1.5f; // Default gravity value
	}
	SetComponentTickEnabled(false);
}

