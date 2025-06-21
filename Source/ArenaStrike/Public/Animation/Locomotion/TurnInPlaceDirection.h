// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TurnInPlaceDirection.generated.h"


/**
 * Representing the direction of or turn in place
 * Calculated on TurnInPlaceEntry state become relevant
 */
UENUM(Blueprintable)
enum class ETurnInPlaceDirection : uint8
{
	Left,
	Right
};
