﻿// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LocomotionDirection.h"
#include "RootYawOffsetMode.h"
#include "TurnInPlaceDirection.h"
#include "Character/Movement/Gait.h"
#include "Kismet/KismetMathLibrary.h"
#include "LocomotionAnimationData.generated.h"

USTRUCT(BlueprintType)
struct ARENASTRIKE_API FLocomotionAnimationData
{
	GENERATED_BODY()

#pragma region Velocity
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Velocity")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Velocity")
	FVector Velocity2D = FVector::ZeroVector;
#pragma endregion

#pragma region Acceleration
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Acceleration")
	FVector Acceleration = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Acceleration")
	FVector Acceleration2D = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Acceleration")
	FVector PivotAcceleration2D = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Acceleration")
	bool bIsAccelerating = false;
#pragma endregion

#pragma region Location
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Location")
	FVector PreviousFrameWorldLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Location")
	FVector WorldLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Location")
	float DeltaWorldLocationLength = ForceInitToZero;
#pragma endregion
	
#pragma region Rotation
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation")
	FRotator Rotation = FRotator::ZeroRotator;

	/**
	 * Yaw in current frame
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation")
	float CurrentYaw = ForceInitToZero;

	/**
	 * Yaw in last frame
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation")
	float LastYaw = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation")
	float DeltaYaw = ForceInitToZero;
#pragma endregion
#pragma region RootYawOffset
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|RootYawOffset")
	float RootYawOffset = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|RootYawOffset")
	float AimPitch = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|RootYawOffset")
	ERootYawOffsetMode RootYawOffsetMode = ERootYawOffsetMode::Hold;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|RootYawOffset")
	FFloatSpringState RootYawOffsetBlendOutInterpolationFloatSpringState;
#pragma endregion

#pragma region TurnInPlace
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|TurnInPlace")
	ETurnInPlaceDirection TurnInPlaceSideDirection = ETurnInPlaceDirection::Left;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|TurnInPlace")
	float TurnInPlaceAnimationTime = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|TurnInPlace")
	UAnimSequence* FinalTurnInPlaceAnimation = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|TurnInPlace")
	float TurnInPlaceYawCurveValue = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|TurnInPlace")
	float PreviousFrameTurnInPlaceYawCurveValue = ForceInitToZero;

#pragma endregion

#pragma region Orientation
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	float VelocityLocomotionAngle = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	float VelocityLocomotionAngleWithRootYawOffset = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	float AccelerationLocomotionAngle = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	ELocomotionDirection PreviousFrameLocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	ELocomotionDirection LocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	ELocomotionDirection AccelerationLocomotionDirection = ELocomotionDirection::Forward;
	
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	float LeanAngle = ForceInitToZero;
#pragma endregion

#pragma region Gait
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait")
	EGait IncomingGait = EGait::Walking;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait")
	EGait PreviousFrameGait = EGait::Walking;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait")
	EGait CurrentGait = EGait::Walking;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait")
	bool bGaitWasChanged = false;
#pragma endregion
};
