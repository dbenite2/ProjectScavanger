// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasePrimaryAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAVANGER_API UBasePrimaryAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasePrimaryAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void BasePrimaryAttack();

	UPROPERTY(EditAnywhere)
	float sphereRadius = 70.f;

	UPROPERTY(EditAnywhere)
	float sphereHalfHeightRadius = 35.f;

	UPROPERTY(EditAnywhere)
	FVector forwardOffset = {60.f, 60.f, 0};		
};
