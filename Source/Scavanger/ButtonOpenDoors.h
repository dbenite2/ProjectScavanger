// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicDoor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ButtonOpenDoors.generated.h"

UCLASS()
class SCAVANGER_API AButtonOpenDoors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonOpenDoors();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category= "Projectile")
	USphereComponent* CollisionComp{nullptr};

	UPROPERTY(VisibleDefaultsOnly, Category= "Projectile")
	UStaticMeshComponent* MeshComponent{nullptr};

public:	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USphereComponent* GetCollisionComp() const;

	UPROPERTY(EditAnywhere)
	ABasicDoor* openDoors;

	UPROPERTY(EditAnywhere, Category = "open Door")
	TSubclassOf<class ABasicDoor> openDoorClass;
};
