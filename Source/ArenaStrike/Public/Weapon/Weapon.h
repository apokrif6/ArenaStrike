// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class ARENASTRIKE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void BeginPlay() override;

	void Equip();

	void Unequip();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Animation")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Animation")
	TSubclassOf<UAnimInstance> AnimationLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Sockets")
	FName UnequippedSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Sockets")
	FName EquippedSocketName;

private:
	UPROPERTY()
	ACharacter* InstigatorCharacter = nullptr;

	void AttachWeaponToUnequippedSocket();
};
