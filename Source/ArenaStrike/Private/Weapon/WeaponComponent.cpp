// Copyright apokrif6. All Rights Reserved


#include "Weapon/WeaponComponent.h"

#include "Animation/Interfaces/ASAnimationInterface.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY(LogASWeaponSystem);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::EquipWeapon(const EEquippedWeapon InEquippedWeapon)
{
	if (EquippedWeapon == InEquippedWeapon)
	{
		return;
	}

	EquippedWeapon = InEquippedWeapon;

	const ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogASWeaponSystem, Error,
		       TEXT("WeaponComponent can be used only with character, but owner %s is not a character"),
		       *GetOwner()->GetName());
		return;
	}

	if (const TSubclassOf<UAnimInstance>* AnimLayerForWeapon = AnimationLayersForWeapons.Find(InEquippedWeapon);
		AnimLayerForWeapon)
	{
		OwnerCharacter->GetMesh()->LinkAnimClassLayers(*AnimLayerForWeapon);
	}
	else
	{
		UE_LOG(LogASWeaponSystem, Warning, TEXT("WeaponComponent for %s does not have animation layer for weapon %s"),
		       *GetOwner()->GetName(), *UEnum::GetValueAsString(InEquippedWeapon));
	}

	if (UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance(); AnimInstance && AnimInstance->
		Implements<UASAnimationInterface>())
	{
		IASAnimationInterface::Execute_ReceiveEquippedWeapon(AnimInstance, InEquippedWeapon);
	}
}
