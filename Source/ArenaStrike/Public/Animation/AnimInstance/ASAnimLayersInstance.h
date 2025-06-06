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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stop|Animations")
	FLocomotionDirectionAnimations WalkingStopLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stop|Animations")
	FLocomotionDirectionAnimations JoggingStopLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Start|Animations")
	FLocomotionDirectionAnimations WalkingStartLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Start|Animations")
	FLocomotionDirectionAnimations JoggingStartLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pivot|Animations")
	FLocomotionDirectionAnimations WalkingPivotLocomotionDirectionAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pivot|Animations")
	FLocomotionDirectionAnimations JoggingPivotLocomotionDirectionAnimations;
};
