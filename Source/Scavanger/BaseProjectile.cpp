// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "IDamageable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);

	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	MeshComponent->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 3.0f;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	// Base OnHit method to do damage with the projectile.
	if (OtherActor && OtherActor != this && OtherComp) {
		
		if (!UKismetSystemLibrary::DoesImplementInterface(OtherActor, UIDamageable::StaticClass())) {
			return;
		}
		IIDamageable* DamageableActor = Cast<IIDamageable>(OtherActor);
		if (!DamageableActor) return;
		DamageableActor->TakeDamage(BaseDamage);
	}

	Destroy();
}

USphereComponent* ABaseProjectile::GetCollisionComp() const {
	return CollisionComp;
}

UProjectileMovementComponent* ABaseProjectile::GetProjectileMovement() const {
	return ProjectileMovement;
}

