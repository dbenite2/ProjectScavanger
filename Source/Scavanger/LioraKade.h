// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Sword.h"
#include "ZeroGravityProjectile.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "LioraKade.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChange, int, WeaponIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletChange, int, BulletIndex);

class ULife_Component;
class UZeroGravityComponent;
class USpringArmComponent;
class UCameraComponent;
class UBasePrimaryAttackComponent;
class UBaseShootAttack;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(Config=Game)
class SCAVANGER_API ALioraKade : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZeroGravity", meta = (AllowPrivateAccess))
	UZeroGravityComponent* ZeroGravityComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MeleeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BaseShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeWeaponAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZeroGravityShootAction;

public:
	ALioraKade();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

	UFUNCTION()
	void SwitchWeapon();


protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MeleeAttack();
	
	void ShootAttack();

	UFUNCTION() void ChangeWeapon();

	void ChangeBullet();

	UPROPERTY(VisibleAnywhere)
	UBasePrimaryAttackComponent* MeleeAttackComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBaseShootAttack* ShootAttackComponent = nullptr;

public:
	ALioraKade();

	UPROPERTY() FOnWeaponChange OnWeaponChange;
	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintReadWrite)
	bool hasWeapon = true;

	UPROPERTY(EditAnywhere)
	AGun* gun;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere)
	ASword* sword;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ASword> swordClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* WeaponSwitchMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* ShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* MeleeAttackMontage;


	UPROPERTY()
	bool ZeroGravityEnable = false;

	UPROPERTY()
	bool gravityBullet = false;

	UPROPERTY(EditAnywhere)
	FVector offset = {60.f, 60.f, 0};

	UPROPERTY(EditAnywhere)
	AZeroGravityProjectile* zeroGravityProjectile;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AZeroGravityProjectile> zeroGravityProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULife_Component* LifeComponent{nullptr};

};
