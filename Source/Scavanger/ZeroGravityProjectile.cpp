// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeroGravityProjectile.h"

#include "ZeroGravityComponent.h"
#include "Components/SphereComponent.h"

AZeroGravityProjectile::AZeroGravityProjectile() {
	if (CollisionComp) {
		CollisionComp->OnComponentHit.AddDynamic(this, &AZeroGravityProjectile::OnHit);
	}
}

void AZeroGravityProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	// Attach ZeroGravityComponent to the hit actor
	if (OtherActor && OtherActor != this) {
		// Check if the hit actor has a ZeroGravityComponent
		UZeroGravityComponent* ZeroGravityComp = OtherActor->FindComponentByClass<UZeroGravityComponent>();
		if (ZeroGravityComp)
		{
			float ZeroGravityDuration = 3.0f; // Example duration
			ZeroGravityComp->ActivateZeroGravity(ZeroGravityDuration);
			UE_LOG(LogTemp, Warning, TEXT("ZeroGravityComponent activated on OtherActor: %s"), *OtherActor->GetName());
		}
	}
}
