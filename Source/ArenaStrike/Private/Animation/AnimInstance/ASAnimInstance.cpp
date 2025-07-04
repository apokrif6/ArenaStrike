﻿// Copyright apokrif6. All Rights Reserved


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

	UpdateVelocityData();
	UpdateAccelerationData();
	UpdateRotationData(DeltaSeconds);
	UpdateRootYawOffsetData(DeltaSeconds);
	UpdateOrientationData();
	UpdateGaitData();
}

void UASAnimInstance::ReceiveIncomingGait_Implementation(const EGait IncomingGait)
{
	LocomotionData.IncomingGait = IncomingGait;

	UpdateGaitData();
}

UASCharacterMovementComponent* UASAnimInstance::GetCharacterMovementComponent() const
{
	if (OwnerCharacter)
	{
		return Cast<UASCharacterMovementComponent>(OwnerCharacter->GetCharacterMovement());
	}

	return nullptr;
}

void UASAnimInstance::SavePivotDataOnPivotStateBecomeRelevant()
{
	LocomotionData.PivotAcceleration2D = LocomotionData.Acceleration2D;
}

void UASAnimInstance::SetRootYawOffsetMode(const ERootYawOffsetMode RootYawOffsetMode)
{
	LocomotionData.RootYawOffsetMode = RootYawOffsetMode;
}

void UASAnimInstance::SetTurnInPlaceDirection(const ETurnInPlaceDirection TurnInPlaceDirection)
{
	LocomotionData.TurnInPlaceSideDirection = TurnInPlaceDirection;
}

float UASAnimInstance::UpdateTurnInPlaceAnimationTime(const float DeltaSeconds)
{
	return LocomotionData.TurnInPlaceAnimationTime += DeltaSeconds;
}

void UASAnimInstance::ResetTurnInPlaceAnimationTime()
{
	LocomotionData.TurnInPlaceAnimationTime = 0.f;
}

void UASAnimInstance::SetFinalTurnInPlaceAnimation(UAnimSequence* FinalTurnInPlaceAnimation)
{
	LocomotionData.FinalTurnInPlaceAnimation = FinalTurnInPlaceAnimation;
}

void UASAnimInstance::ProcessTurnInPlaceYawCurve()
{
	LocomotionData.PreviousFrameTurnInPlaceYawCurveValue = LocomotionData.TurnInPlaceYawCurveValue;

	// if true, we are recovering from turn in place. if false, we are turning in place
	if (const float IsTurningCurveValue = GetCurveValue(IsTurningCurveName); IsTurningCurveValue < 1.f)
	{
		LocomotionData.PreviousFrameTurnInPlaceYawCurveValue = 0.f;
		LocomotionData.TurnInPlaceYawCurveValue = 0.f;
	}
	else
	{
		LocomotionData.TurnInPlaceYawCurveValue = UKismetMathLibrary::SafeDivide(
			GetCurveValue(TurnInPlaceYawCurveName), IsTurningCurveValue);

		if (LocomotionData.PreviousFrameTurnInPlaceYawCurveValue != 0.f)
		{
			SetRootYawOffset(LocomotionData.RootYawOffset - (LocomotionData.TurnInPlaceYawCurveValue - LocomotionData.
				PreviousFrameTurnInPlaceYawCurveValue));
		}
	}
}

void UASAnimInstance::SetRootYawOffset(const float Angle)
{
	LocomotionData.RootYawOffset = UKismetMathLibrary::NormalizeAxis(Angle);
}

void UASAnimInstance::UpdateVelocityData()
{
	LocomotionData.Velocity = GetCharacterMovementComponent()->Velocity;
	LocomotionData.Velocity2D = LocomotionData.Velocity * FVector{1.f, 1.f, 0.f};
}

void UASAnimInstance::UpdateAccelerationData()
{
	LocomotionData.Acceleration = GetCharacterMovementComponent()->GetCurrentAcceleration();
	LocomotionData.Acceleration2D = LocomotionData.Acceleration * FVector{1.f, 1.f, 0.f};
	LocomotionData.bIsAccelerating = !FMath::IsNearlyEqual(LocomotionData.Acceleration2D.Size2D(), 0.f);
}

void UASAnimInstance::UpdateLocationData()
{
	LocomotionData.PreviousFrameWorldLocation = LocomotionData.WorldLocation;
	LocomotionData.WorldLocation = OwnerCharacter->GetActorLocation();
	LocomotionData.DeltaWorldLocationLength = (LocomotionData.WorldLocation - LocomotionData.PreviousFrameWorldLocation)
		.Size();
}

void UASAnimInstance::UpdateRotationData(const float DeltaSeconds)
{
	LocomotionData.Rotation = OwnerCharacter->GetActorRotation();
	LocomotionData.LastYaw = LocomotionData.CurrentYaw;
	LocomotionData.CurrentYaw = LocomotionData.Rotation.Yaw;
	LocomotionData.DeltaYaw = LocomotionData.CurrentYaw - LocomotionData.LastYaw;

	LocomotionData.AimPitch = UKismetMathLibrary::NormalizeAxis(OwnerCharacter->GetBaseAimRotation().Pitch);

	float InterpolatedYaw = UKismetMathLibrary::SafeDivide(LocomotionData.DeltaYaw, DeltaSeconds) / 4.f;
	if (LocomotionData.LocomotionDirection == ELocomotionDirection::Backward)
	{
		//inverse for backward additive lean
		InterpolatedYaw *= -1.f;
	}

	LocomotionData.LeanAngle = FMath::ClampAngle(InterpolatedYaw, -90.f, 90.f);
}

void UASAnimInstance::UpdateRootYawOffsetData(const float DeltaSeconds)
{
	if (LocomotionData.RootYawOffsetMode == ERootYawOffsetMode::Accumulate)
	{
		SetRootYawOffset(LocomotionData.RootYawOffset + LocomotionData.DeltaYaw * -1.f);
	}
	if (LocomotionData.RootYawOffsetMode == ERootYawOffsetMode::BlendOut)
	{
		LocomotionData.RootYawOffset = UKismetMathLibrary::FloatSpringInterp(LocomotionData.RootYawOffset,
		                                                                     0.f, LocomotionData.
		                                                                     RootYawOffsetBlendOutInterpolationFloatSpringState,
		                                                                     80.f, 1.f,
		                                                                     DeltaSeconds, 1.f, 0.5f);
	}
	LocomotionData.RootYawOffsetMode = ERootYawOffsetMode::BlendOut;
}

void UASAnimInstance::UpdateOrientationData()
{
	LocomotionData.PreviousFrameLocomotionDirection = LocomotionData.LocomotionDirection;

	LocomotionData.VelocityLocomotionAngle = UKismetAnimationLibrary::CalculateDirection(
		LocomotionData.Velocity2D, LocomotionData.Rotation);

	LocomotionData.VelocityLocomotionAngleWithRootYawOffset = UKismetMathLibrary::NormalizeAxis(
		LocomotionData.VelocityLocomotionAngle - LocomotionData.RootYawOffset);

	LocomotionData.AccelerationLocomotionAngle = UKismetAnimationLibrary::CalculateDirection(
		LocomotionData.Acceleration2D, LocomotionData.Rotation);

	LocomotionData.LocomotionDirection = CalculateLocomotionDirection(LocomotionData.LocomotionDirection,
	                                                                  LocomotionData.VelocityLocomotionAngle, -130.f,
	                                                                  130.f,
	                                                                  -50.f, 50.f, 20.f);

	LocomotionData.AccelerationLocomotionDirection = CalculateLocomotionDirection(
		LocomotionData.AccelerationLocomotionDirection,
		LocomotionData.AccelerationLocomotionAngle, -130.f,
		130.f,
		-50.f, 50.f, 20.f);
}

void UASAnimInstance::UpdateGaitData()
{
	LocomotionData.PreviousFrameGait = LocomotionData.CurrentGait;
	LocomotionData.CurrentGait = LocomotionData.IncomingGait;
	LocomotionData.bGaitWasChanged = LocomotionData.PreviousFrameGait != LocomotionData.CurrentGait;
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
