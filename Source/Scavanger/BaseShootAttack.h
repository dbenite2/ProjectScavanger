// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Components/ActorComponent.h"
#include "BaseShootAttack.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAVANGER_API UBaseShootAttack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseShootAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void BaseShootAttack();

	UPROPERTY(EditAnywhere)
	float range = 500.f;

	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	UPROPERTY(EditAnywhere)
	FVector offset = {60.f, 60.f, 0};

	// UPROPERTY(EditAnywhere)
	// AGun * gun  = nullptr;
		
};
