// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicDoor.generated.h"

UCLASS()
class SCAVANGER_API ABasicDoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Model")
	UStaticMeshComponent* Mesh{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	bool bShouldMove{false};
	
public:	
	// Sets default values for this actor's properties
	ABasicDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DestroyDoors();

};
