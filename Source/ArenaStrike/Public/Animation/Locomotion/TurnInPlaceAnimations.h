// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TurnInPlaceAnimations.generated.h"

/**
 * Container for TurnInPlace animations used by layers
 */
USTRUCT(BlueprintType)
struct ARENASTRIKE_API FTurnInPlaceAnimations
{
	GENERATED_BODY()

	/**
	 * 90 degrees
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	TObjectPtr<UAnimSequence> LeftQuarter;

	/**
	 * 180 degrees
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	TObjectPtr<UAnimSequence> LeftHalf;

	/**
	 * 90 degrees
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	TObjectPtr<UAnimSequence> RightQuarter;

	/**
	 * 180 degrees
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	TObjectPtr<UAnimSequence> RightHalf;
};