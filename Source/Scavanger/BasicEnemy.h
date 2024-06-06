// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "Life_Component.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.generated.h"

UCLASS()
class SCAVANGER_API ABasicEnemy : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamage(float damage) override;

	UPROPERTY(EditAnywhere)
	ULife_Component* HealthComponent;
};
