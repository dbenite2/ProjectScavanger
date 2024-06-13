// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeroGravityProjectile.h"

#include "Components/SphereComponent.h"

AZeroGravityProjectile::AZeroGravityProjectile() {
	if (CollisionComp) {
		CollisionComp->OnComponentHit.AddDynamic(this, &AZeroGravityProjectile::OnHit);
	}
}

void AZeroGravityProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && OtherActor != this)
	{
		// Check if the other actor has a primitive component
		UPrimitiveComponent* OtherPrimitiveComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
		if (OtherPrimitiveComp)
		{
			// Apply an upward force to counteract gravity
			FVector Gravity(0.f, 0.f, -GetWorld()->GetGravityZ());
			FVector CounteractForce = -Gravity * OtherPrimitiveComp->GetMass();

			OtherPrimitiveComp->AddForce(CounteractForce);
			UE_LOG(LogTemp, Warning, TEXT("Applied counteracting force to OtherActor: %s"), *OtherActor->GetName());
		}
	}
}
