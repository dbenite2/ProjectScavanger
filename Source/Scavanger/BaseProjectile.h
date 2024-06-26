
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SCAVANGER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

	

	
protected:

	UPROPERTY(EditDefaultsOnly, Category="Projectile Values")
	int32 BaseDamage{0};
	
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement{nullptr};

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	UStaticMeshComponent* MeshComponent{nullptr};

	
public:	
	ABaseProjectile();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USphereComponent* GetCollisionComp() const;

	UProjectileMovementComponent* GetProjectileMovement() const;
	
};
