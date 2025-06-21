// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UGameplayEffect;

UCLASS()
class ARENASTRIKE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void BeginPlay() override;

	void Equip();

	void Unequip();

	USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|GAS")
	TSubclassOf<UGameplayEffect> EquippedWeaponGameplayEffectToApplyToInstigator;

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

	FActiveGameplayEffectHandle EquippedWeaponGameplayEffectHandle;
};
