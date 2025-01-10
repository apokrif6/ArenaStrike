// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/EquippedWeapon.h"
#include "WeaponComponent.generated.h"


enum class EEquippedWeapon : uint8;

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class ARENASTRIKE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	EEquippedWeapon GetEquippedWeapon() const { return EquippedWeapon; }

	void SetEquippedWeapon(const EEquippedWeapon InEquippedWeapon) { EquippedWeapon = InEquippedWeapon; }

private:
	EEquippedWeapon EquippedWeapon;
};
