// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LocomotionDirection.h"
#include "LocomotionAnimationData.generated.h"

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
	bool bIsAccelerating = false;
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

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float VelocityLocomotionAngle = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	ELocomotionDirection LocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float LeanAngle = ForceInitToZero;
};
