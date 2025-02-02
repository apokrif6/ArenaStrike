// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LocomotionDirection.generated.h"

UENUM(Blueprintable)
enum class ELocomotionDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};
