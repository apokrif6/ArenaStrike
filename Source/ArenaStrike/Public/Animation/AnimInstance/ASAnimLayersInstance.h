// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/Locomotion/LocomotionDirectionAnimations.h"
#include "ASAnimLayersInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENASTRIKE_API UASAnimLayersInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cycle|Animations")
	FLocomotionDirectionAnimations WalkingCycleLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cycle|Animations")
	FLocomotionDirectionAnimations JoggingCycleLocomotionDirectionAnimations;
};
