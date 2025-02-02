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

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	FVector Velocity2D = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float VelocityLocomotionAngle = ForceInitToZero;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	ELocomotionDirection LocomotionDirection = ELocomotionDirection::Forward;
};
