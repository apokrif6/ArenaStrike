// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/EquippedWeapon.h"
#include "WeaponComponent.generated.h"


class AWeapon;
enum class EEquippedWeapon : uint8;

DECLARE_LOG_CATEGORY_EXTERN(LogASWeaponSystem, Log, All);

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class ARENASTRIKE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeapon* GetEquippedWeapon() const { return EquippedWeaponActor; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(const EEquippedWeapon InEquippedWeapon);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	TMap<EEquippedWeapon, TSubclassOf<AWeapon>> StartupWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons|Animation")
	TSubclassOf<UAnimInstance> UnarmedAnimationLayer;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter = nullptr;
	
	UPROPERTY()
	AWeapon* EquippedWeaponActor = nullptr;

	UPROPERTY()
	TMap<EEquippedWeapon, AWeapon*> SpawnedWeapons;
};
