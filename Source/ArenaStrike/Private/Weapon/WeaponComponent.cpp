// Copyright apokrif6. All Rights Reserved


#include "Weapon/WeaponComponent.h"

#include "Animation/Interfaces/ASAnimationInterface.h"
#include "GameFramework/Character.h"
#include "Weapon/Weapon.h"

DEFINE_LOG_CATEGORY(LogASWeaponSystem);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	check(OwnerCharacter)
	
	for (auto AvailableWeapon : StartupWeapons)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = Cast<APawn>(GetOwner());
		if (AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(AvailableWeapon.Value, FTransform::Identity,
		                                                             ActorSpawnParameters))
		{
			SpawnedWeapons.Add(AvailableWeapon.Key, SpawnedWeapon);
		}
		else
		{
			UE_LOG(LogASWeaponSystem, Error, TEXT("Failed to spawn weapon %s"), *AvailableWeapon.Value->GetName());
		}
	}
}

void UWeaponComponent::EquipWeapon(const EEquippedWeapon InEquippedWeapon)
{
	if (const EEquippedWeapon* EquippedWeapon = SpawnedWeapons.FindKey(EquippedWeaponActor);
		EquippedWeapon && *EquippedWeapon == InEquippedWeapon)
	{
		return;
	}

	if (EquippedWeaponActor)
	{
		EquippedWeaponActor->Unequip();
	}
	
	if (InEquippedWeapon == EEquippedWeapon::Unarmed)
	{
		EquippedWeaponActor = nullptr;
		OwnerCharacter->GetMesh()->LinkAnimClassLayers(UnarmedAnimationLayer);
	}
	
	if (SpawnedWeapons.Find(InEquippedWeapon))
	{
		if (EquippedWeaponActor)
		{
			EquippedWeaponActor->Unequip();
		}
		EquippedWeaponActor = *SpawnedWeapons.Find(InEquippedWeapon);
	}
	else
	{
		UE_LOG(LogASWeaponSystem, Error, TEXT("Failed to equip weapon %s. Can't find associated spawned weapon"),
		       *UEnum::GetValueAsString(InEquippedWeapon));
		return;
	}

	EquippedWeaponActor->Equip();

	if (UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance(); AnimInstance && AnimInstance->
		Implements<UASAnimationInterface>())
	{
		IASAnimationInterface::Execute_ReceiveEquippedWeapon(AnimInstance, InEquippedWeapon);
	}
}
