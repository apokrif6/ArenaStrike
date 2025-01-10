// Copyright apokrif6. All Rights Reserved

#include "ArenaStrike/Public/Character/ASCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "..\..\Public\Animation\Interfaces\ASAnimationInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/WeaponComponent.h"

AASCharacter::AASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void AASCharacter::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(SwitchWeaponInputAction, ETriggerEvent::Triggered, this,
		                                   &ThisClass::SwitchWeapon);
	}
}

void AASCharacter::SwitchWeapon(const FInputActionValue& Value)
{
	const int TruncatedValue = UKismetMathLibrary::FTrunc(Value.Get<float>());

	//TODO
	//create better implementation
	//maybe cast int to uenum?
	EEquippedWeapon NewWeapon;
	switch (TruncatedValue)
	{
	case 1:
		NewWeapon = EEquippedWeapon::Unarmed;
		break;
	case 2:
		NewWeapon = EEquippedWeapon::Pistol;
		break;
	case 3:
		NewWeapon = EEquippedWeapon::Rifle;
		break;
	default:
		NewWeapon = EEquippedWeapon::Unarmed;
	}

	WeaponComponent->SetEquippedWeapon(NewWeapon);
	
	if (const UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && AnimInstance->Implements<UASAnimationInterface>())
	{
		IASAnimationInterface::Execute_ReceiveEquippedWeapon(GetMesh()->GetAnimInstance(), NewWeapon);
	}
}
