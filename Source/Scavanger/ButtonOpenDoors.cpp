// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonOpenDoors.h"
#include "Engine.h"
#include "BasicDoor.h"
#include "LioraKade.h"

// Sets default values
AButtonOpenDoors::AButtonOpenDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AButtonOpenDoors::OnHit);

	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AButtonOpenDoors::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	ALioraKade* player = Cast<ALioraKade>(OtherActor);

	if (player)
	{
		if(player->ZeroGravityEnable)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicDoor::StaticClass(), FoundActors);

			UE_LOG(LogTemp, Log, TEXT("Entro1"));
			
			for (auto* Actor: FoundActors) {
				if (ABasicDoor* BasicDoor = Cast<ABasicDoor>(Actor)) {
					BasicDoor->DestroyDoors();
					UE_LOG(LogTemp, Log, TEXT("Entro"));
				}
			}
		}
	}
}

USphereComponent* AButtonOpenDoors::GetCollisionComp() const {
	return CollisionComp;
}

