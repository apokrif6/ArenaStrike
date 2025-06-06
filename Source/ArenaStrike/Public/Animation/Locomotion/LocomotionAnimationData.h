// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LocomotionDirection.h"
#include "Character/Movement/Gait.h"
#include "LocomotionAnimationData.generated.h"

enum class EGait : uint8;
enum class ELocomotionDirection : uint8;

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

#pragma region Orientation
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Orientation")
	float VelocityLocomotionAngle = ForceInitToZero;

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
