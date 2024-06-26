#include "LioraKade.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "BasePrimaryAttackComponent.h"
#include "BaseShootAttack.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ZeroGravityComponent.h"

// Sets default values
ALioraKade::ALioraKade()
{
	PrimaryActorTick.bCanEverTick = false; // activate if necessary
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // template size, not final
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance in front of the character
	// Lock the camera location and rotation.
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritPitch = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	ZeroGravityComp = CreateDefaultSubobject<UZeroGravityComponent>(TEXT("ZeroGravity"));
	
	MeleeAttackComponent = CreateDefaultSubobject<UBasePrimaryAttackComponent>(TEXT("BasePrimaryAttack"));
	ShootAttackComponent = CreateDefaultSubobject<UBaseShootAttack>(TEXT("BaseShootAttack"));
}

// Called when the game starts or when spawned
void ALioraKade::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("WeaponSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("WeaponSocket"));

	gun = GetWorld()->SpawnActor<AGun>(GunClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (gun)
	{
		gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("WeaponSocket"));
	}
}

// Called every frame
void ALioraKade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALioraKade::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALioraKade::Move);

		EnhancedInputComponent->BindAction(MeleeAttackAction, ETriggerEvent::Triggered, this, &ALioraKade::MeleeAttack);

		EnhancedInputComponent->BindAction(BaseShootAction, ETriggerEvent::Triggered, this, &ALioraKade::ShootAttack);

		EnhancedInputComponent->BindAction(ChangeWeaponAction, ETriggerEvent::Triggered, this, &ALioraKade::ChangeWeapon);
		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALioraKade::MeleeAttack()
{
	if(!hasWeapon)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(ShootMontage))
		{
			AnimInstance->Montage_Play(MeleeAttackMontage);
			MeleeAttackComponent->BasePrimaryAttack();
		}
	}
}

void ALioraKade::ShootAttack()
{
	if(hasWeapon)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(ShootMontage))
		{
			AnimInstance->Montage_Play(ShootMontage);
		}
		ShootAttackComponent->BaseShootAttack();
	}
}

void ALioraKade::ChangeWeapon()
{
	if (WeaponSwitchMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(WeaponSwitchMontage))
		{
			AnimInstance->Montage_Play(WeaponSwitchMontage);

			// Delay the weapon switch until the montage ends
			// FTimerHandle UnusedHandle;
			// GetWorldTimerManager().SetTimer(UnusedHandle, this, &ALioraKade::SwitchWeapon, WeaponSwitchMontage->GetPlayLength(), false);

			FTimerHandle LioraHandle;
			GetWorldTimerManager().SetTimer(LioraHandle, this, &ALioraKade::SwitchWeapon, WeaponSwitchMontage->GetPlayLength(), false);
		}
	}
}

void ALioraKade::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.X);
	}
}

void ALioraKade::SwitchWeapon()
{
	hasWeapon = !hasWeapon;

	const TCHAR* BoolString = hasWeapon ? TEXT("true") : TEXT("false");

	UE_LOG(LogTemp, Log, TEXT("The value of the boolean variable is: %s"), BoolString);

	if(hasWeapon)
	{
		sword->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		sword->Destroy(false);
		sword = nullptr;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("WeaponSocket"));
		FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("WeaponSocket"));

		gun = GetWorld()->SpawnActor<AGun>(GunClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (gun)
		{
			gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("WeaponSocket"));
		}
	}

	if(!hasWeapon)
	{
		gun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		gun->Destroy(false);
		gun = nullptr;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("WeaponSocket"));
		FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("WeaponSocket"));

		sword = GetWorld()->SpawnActor<ASword>(swordClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (sword)
		{
			sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("WeaponSocket"));
		}
	}
}
