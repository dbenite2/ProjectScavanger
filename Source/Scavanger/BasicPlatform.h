// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicPlatform.generated.h"

UCLASS()
class SCAVANGER_API ABasicPlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Model")
	UStaticMeshComponent* Mesh{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	bool bShouldMove{false};
	
public:	
	ABasicPlatform();

	virtual void Tick(float DeltaTime) override;
	
protected:
	
	virtual void BeginPlay() override;
	
};
