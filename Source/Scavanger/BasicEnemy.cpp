// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<ULife_Component>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicEnemy::TakeDamage(float damage)
{
	if(HealthComponent)
	{
		HealthComponent->ModifyHealth(damage);
	}
}

