// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Life_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLifeChange, int, current, int, max);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAVANGER_API ULife_Component : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	
	ULife_Component();

	FOnLifeChange OnLifeChange;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth{100};

	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth{100};

	UFUNCTION(BlueprintCallable)
	void ModifyHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void ActorDie();
};
