#include "BasicRoom.h"

ABasicRoom::ABasicRoom()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SceneComponent->SetupAttachment(RootComponent);

	FloorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	FloorComponent->SetupAttachment(SceneComponent);
	CeilComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceil"));
	CeilComponent->SetupAttachment(SceneComponent);
	WallsRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Walls Pivot"));
	WallsRootComponent->SetupAttachment(SceneComponent);
	BackWallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Wall"));
	BackWallComponent->SetupAttachment(WallsRootComponent);
	SideWallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Wall"));
	SideWallComponent->SetupAttachment(WallsRootComponent);
	FrontWallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Wall"));
	FrontWallComponent->SetupAttachment(WallsRootComponent);
	
}

void ABasicRoom::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

