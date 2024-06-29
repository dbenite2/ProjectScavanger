// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeroGravityAbility.h"
#include "LioraKade.h"

// Sets default values
AZeroGravityAbility::AZeroGravityAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AZeroGravityAbility::OnHit);

	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AZeroGravityAbility::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	ALioraKade* player = Cast<ALioraKade>(OtherActor);

	if (player)
	{
		player->ZeroGravityEnable = true;
	}

	Destroy();
}

USphereComponent* AZeroGravityAbility::GetCollisionComp() const {
	return CollisionComp;
}

