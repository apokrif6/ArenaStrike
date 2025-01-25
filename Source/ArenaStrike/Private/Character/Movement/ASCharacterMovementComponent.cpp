// Copyright apokrif6. All Rights Reserved


#include "Character/Movement/ASCharacterMovementComponent.h"

#include "Animation/Interfaces/ASAnimationInterface.h"
#include "Character/ASCharacter.h"

UASCharacterMovementComponent::UASCharacterMovementComponent()
{
}

void UASCharacterMovementComponent::SetGait(const EGait InGait)
{
	if (CurrentGait == InGait)
	{
		return;
	}

	CurrentGait = InGait;

	if (const FGaitSettings* CurrentGaitSettings = GaitSettings.Find(CurrentGait); CurrentGaitSettings)
	{
		MaxWalkSpeed = CurrentGaitSettings->MaxSpeed;
		MaxAcceleration = CurrentGaitSettings->MaxAcceleration;
		BrakingDecelerationWalking = CurrentGaitSettings->BrakingDeceleration;
		BrakingFrictionFactor = CurrentGaitSettings->BrakingFrictionFactor;
		bUseSeparateBrakingFriction = CurrentGaitSettings->bUseSeparateBrakingFriction;
		BrakingFriction = CurrentGaitSettings->BrakingFriction;
	}
	else
	{
		UE_LOG(LogASCharacter, Warning, TEXT("Gait settings for %s for %s are not set"),
		       *UEnum::GetValueAsString(InGait), *GetOwner()->GetName());
	}

	if (UAnimInstance* AnimInstance = GetCharacterOwner()->GetMesh()->GetAnimInstance(); AnimInstance &&
		AnimInstance->Implements<UASAnimationInterface>())
	{
		IASAnimationInterface::Execute_ReceiveCurrentGait(AnimInstance, CurrentGait);
	}
}

void UASCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetGait(EGait::Jogging);
}
