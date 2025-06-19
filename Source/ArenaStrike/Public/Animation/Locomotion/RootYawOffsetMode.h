// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "RootYawOffsetMode.generated.h"

/**
 * Representing the mode of root yaw offset
 * Used to determine that we should turn in place during idle, and not turn during cycle
 */
UENUM(Blueprintable)
enum class ERootYawOffsetMode : uint8
{
	Hold,
	Accumulate,
	BlendOut
};
