// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ZeroGravityAbility.generated.h"

UCLASS()
class SCAVANGER_API AZeroGravityAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZeroGravityAbility();

protected:

	UPROPERTY(VisibleDefaultsOnly, Category= "Projectile")
	USphereComponent* CollisionComp{nullptr};

	UPROPERTY(VisibleDefaultsOnly, Category= "Projectile")
	UStaticMeshComponent* MeshComponent{nullptr};

public:	

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USphereComponent* GetCollisionComp() const;
};
