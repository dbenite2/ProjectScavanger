// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Sword.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "LioraKade.generated.h"

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

protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MeleeAttack();
	
	void ShootAttack();

	void ChangeWeapon();

	UPROPERTY(VisibleAnywhere)
	UBasePrimaryAttackComponent* MeleeAttackComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBaseShootAttack* ShootAttackComponent = nullptr;

public:
	ALioraKade();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SwitchWeapon();

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULife_Component* LifeComponent{nullptr};
};
