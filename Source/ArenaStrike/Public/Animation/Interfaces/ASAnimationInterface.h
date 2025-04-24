// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASAnimationInterface.generated.h"

enum class EEquippedWeapon : uint8;
enum class EGait : uint8;

UINTERFACE()
class UASAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

class ARENASTRIKE_API IASAnimationInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void ReceiveEquippedWeapon(const EEquippedWeapon EquippedWeapon);

	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void ReceiveIncomingGait(const EGait CurrentGait);
};
