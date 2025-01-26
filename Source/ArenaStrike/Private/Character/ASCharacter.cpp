// Copyright apokrif6. All Rights Reserved

#include "ArenaStrike/Public/Character/ASCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayAbilitySpec.h"
#include "Animation/Interfaces/ASAnimationInterface.h"
#include "AbilitySystem/Input/GameplayAbilitiesInputBindingsDataAsset.h"
#include "Camera/CameraComponent.h"
#include "Character/Movement/ASCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/WeaponComponent.h"

DEFINE_LOG_CATEGORY(LogASCharacter);

AASCharacter::AASCharacter(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UASCharacterMovementComponent>(CharacterMovementComponentName))
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

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void AASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeGameplayAbilitySystem();
}

void AASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}

void AASCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->LinkAnimClassLayers(AnimLayersClass);

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
		if (GameplayAbilitiesInputBindings)
		{
			for (const FGameplayInputAbilityInfo& InputAbility : GameplayAbilitiesInputBindings->GetInputAbilities())
			{
				if (InputAbility.IsValid())
				{
					const UInputAction* InputAction = InputAbility.InputAction;
					const int32 InputID = InputAbility.InputID;

					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this,
					                                   &ThisClass::OnAbilityInputPressed, InputID);
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this,
					                                   &ThisClass::OnAbilityInputReleased, InputID);
				}
			}
		}

		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this,
		                                   &ThisClass::Look);

		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this,
		                                   &ThisClass::Move);
	}
}

void AASCharacter::InitializeGameplayAbilitySystem() const
{
	if (!GameplayAbilitiesInputBindings)
	{
		return;
	}

	for (const FGameplayInputAbilityInfo& InputAbility : GameplayAbilitiesInputBindings->GetInputAbilities())
	{
		if (InputAbility.IsValid())
		{
			const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec{
				InputAbility.GameplayAbilityClass.LoadSynchronous(), 1,
				InputAbility.InputID
			};
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void AASCharacter::OnAbilityInputPressed(int32 InputID)
{
	AbilitySystemComponent->AbilityLocalInputPressed(InputID);
}

void AASCharacter::OnAbilityInputReleased(int32 InputID)
{
	AbilitySystemComponent->AbilityLocalInputReleased(InputID);
}

void AASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AASCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation{0, Rotation.Yaw, 0};

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
