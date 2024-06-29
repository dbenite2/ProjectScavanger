// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "ZeroGravityProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SCAVANGER_API AZeroGravityProjectile : public ABaseProjectile
{
	GENERATED_BODY()

	AZeroGravityProjectile();
	
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* movementP;
};
