#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicRoom.generated.h"

UCLASS()
class SCAVANGER_API ABasicRoom : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	USceneComponent* SceneComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	UStaticMeshComponent* FloorComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	UStaticMeshComponent* CeilComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	USceneComponent* WallsRootComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	UStaticMeshComponent* SideWallComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	UStaticMeshComponent* BackWallComponent{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Room Structure")
	UStaticMeshComponent* FrontWallComponent{nullptr};
	
public:	
	ABasicRoom();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
