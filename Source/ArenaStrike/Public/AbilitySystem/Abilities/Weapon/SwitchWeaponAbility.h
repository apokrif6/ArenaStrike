// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ASGameplayAbility.h"
#include "UObject/Object.h"
#include "SwitchWeaponAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARENASTRIKE_API USwitchWeaponAbility : public UASGameplayAbility
{
	GENERATED_BODY()

	virtual void OnTriggeredInputAction(const FInputActionValue& Value) override;
};
