// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeroGravityComponent.generated.h"


class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAVANGER_API UZeroGravityComponent : public UActorComponent
{
	GENERATED_BODY()

	FVector PreviousLocation;
	FTimerHandle ZeroGravityTimerHandle;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovement{nullptr};

	void DeactivateZeroGravity();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Gravity Values")
	float MinGravityValue{0.f};

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UZeroGravityComponent();

	void ActivateZeroGravity(float Duration);
};
