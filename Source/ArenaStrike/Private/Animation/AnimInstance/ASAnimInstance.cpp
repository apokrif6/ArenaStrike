// Copyright apokrif6. All Rights Reserved


#include "ArenaStrike/Public/Animation/AnimInstance/ASAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/ASCharacter.h"
#include "Character/Movement/ASCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UASAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<AASCharacter>(TryGetPawnOwner());

	Super::NativeInitializeAnimation();
}

void UASAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (UNLIKELY(!OwnerCharacter))
	{
		return;
	}

	GetVelocityData();
	GetRotationData(DeltaSeconds);
	UpdateOrientationData();
	LocomotionData.LocomotionDirection = CalculateLocomotionDirection(LocomotionData.LocomotionDirection,
	                                                                  LocomotionData.VelocityLocomotionAngle, -130.f,
	                                                                  130.f,
	                                                                  -50.f, 50.f, 20.f);
}

UASCharacterMovementComponent* UASAnimInstance::GetCharacterMovementComponent() const
{
	if (OwnerCharacter)
	{
		return Cast<UASCharacterMovementComponent>(OwnerCharacter->GetCharacterMovement());
	}

	return nullptr;
}

void UASAnimInstance::GetVelocityData()
{
	LocomotionData.Velocity = GetCharacterMovementComponent()->Velocity;
	LocomotionData.Velocity2D = LocomotionData.Velocity * FVector{1.f, 1.f, 0.f};
}

void UASAnimInstance::GetRotationData(const float DeltaSeconds)
{
	LocomotionData.Rotation = OwnerCharacter->GetActorRotation();
	LocomotionData.LastYaw = LocomotionData.CurrentYaw;
	LocomotionData.CurrentYaw = LocomotionData.Rotation.Yaw;
	LocomotionData.DeltaYaw = LocomotionData.CurrentYaw - LocomotionData.LastYaw;

	float InterpolatedYaw = UKismetMathLibrary::SafeDivide(LocomotionData.DeltaYaw, DeltaSeconds) / 4.f;
	if (LocomotionData.LocomotionDirection == ELocomotionDirection::Backward)
	{
		//inverse for backward additive lean
		InterpolatedYaw *= -1.f;
	}

	LocomotionData.LeanAngle = FMath::ClampAngle(InterpolatedYaw, -90.f, 90.f);
}

void UASAnimInstance::UpdateOrientationData()
{
	LocomotionData.VelocityLocomotionAngle = UKismetAnimationLibrary::CalculateDirection(
		LocomotionData.Velocity2D, LocomotionData.Rotation);
}

ELocomotionDirection UASAnimInstance::CalculateLocomotionDirection(
	const ELocomotionDirection CurrentLocomotionDirection, const float CurrentLocomotionAngle,
	const float BackwardMinThreshold, const float BackwardMaxThreshold, const float ForwardMinThreshold,
	const float ForwardMaxThreshold, const float Deadzone)
{
	switch (CurrentLocomotionDirection)
	{
	case ELocomotionDirection::Forward:
		if (UKismetMathLibrary::InRange_FloatFloat(CurrentLocomotionAngle, ForwardMinThreshold - Deadzone,
		                                           ForwardMaxThreshold + Deadzone,
		                                           true,
		                                           true))
		{
			return ELocomotionDirection::Forward;
		}
		break;
	case ELocomotionDirection::Backward:
		if (CurrentLocomotionAngle < BackwardMinThreshold + Deadzone ||
			CurrentLocomotionAngle > BackwardMaxThreshold - Deadzone)
		{
			return ELocomotionDirection::Backward;
		}
		break;
	case ELocomotionDirection::Left:
		if (UKismetMathLibrary::InRange_FloatFloat(CurrentLocomotionAngle, BackwardMinThreshold - Deadzone,
		                                           ForwardMinThreshold + Deadzone,
		                                           true,
		                                           true))
		{
			return ELocomotionDirection::Left;
		}
		break;
	case ELocomotionDirection::Right:
		if (UKismetMathLibrary::InRange_FloatFloat(CurrentLocomotionAngle, ForwardMaxThreshold - Deadzone,
		                                           BackwardMaxThreshold + Deadzone,
		                                           true,
		                                           true))
		{
			return ELocomotionDirection::Right;
		}
		break;
	default: ;
	}

	if (CurrentLocomotionAngle < BackwardMinThreshold || CurrentLocomotionAngle > BackwardMaxThreshold)
	{
		return ELocomotionDirection::Backward;
	}

	if (UKismetMathLibrary::InRange_FloatFloat(CurrentLocomotionAngle, ForwardMinThreshold, ForwardMaxThreshold, true,
	                                           true))
	{
		return ELocomotionDirection::Forward;
	}

	if (CurrentLocomotionAngle > 0.f)
	{
		return ELocomotionDirection::Right;
	}

	return ELocomotionDirection::Left;
}
