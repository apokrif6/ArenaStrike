// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/EquippedWeapon.h"
#include "WeaponComponent.generated.h"


enum class EEquippedWeapon : uint8;

DECLARE_LOG_CATEGORY_EXTERN(LogASWeaponSystem, Log, All);

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class ARENASTRIKE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	EEquippedWeapon GetEquippedWeapon() const { return EquippedWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(const EEquippedWeapon InEquippedWeapon);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Animation")
	TMap<EEquippedWeapon, TSubclassOf<UAnimInstance>> AnimationLayersForWeapons;

private:
	EEquippedWeapon EquippedWeapon = EEquippedWeapon::Unarmed;
};
