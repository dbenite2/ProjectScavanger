// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicDoor.h"

#include "ButtonOpenDoors.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasicDoor::ABasicDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform model"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasicDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicDoor::DestroyDoors()
{
	Destroy();
}

