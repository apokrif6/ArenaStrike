// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/Interfaces/ASAnimationInterface.h"
#include "ASAnimInstance.generated.h"

/**
 * Base class for anim blueprints
 */
UCLASS()
class ARENASTRIKE_API UASAnimInstance : public UAnimInstance, public IASAnimationInterface
{
	GENERATED_BODY()
};
