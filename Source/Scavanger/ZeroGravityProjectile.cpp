// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeroGravityProjectile.h"

#include "ZeroGravityComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AZeroGravityProjectile::AZeroGravityProjectile() {
	if (CollisionComp) {
		CollisionComp->OnComponentHit.AddDynamic(this, &AZeroGravityProjectile::OnHit);
	}

	movementP = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	movementP->InitialSpeed = 50000.f;
	movementP->MaxSpeed = 50000.f;
}

void AZeroGravityProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	// Attach ZeroGravityComponent to the hit actor
	if (OtherActor && OtherActor != this) {
		// Check if the hit actor has a ZeroGravityComponent
		UZeroGravityComponent* ZeroGravityComp = OtherActor->FindComponentByClass<UZeroGravityComponent>();
		if (ZeroGravityComp) {
			float ZeroGravityDuration = 3.0f;
			ZeroGravityComp->ActivateZeroGravity(ZeroGravityDuration);
			UE_LOG(LogTemp, Warning, TEXT("ZeroGravityComponent activated on OtherActor: %s"), *OtherActor->GetName());
		}
	}
}