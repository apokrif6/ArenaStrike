// Copyright apokrif6. All Rights Reserved


#include "Weapon/Weapon.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	InstigatorCharacter = Cast<ACharacter>(GetInstigator());
	if (!InstigatorCharacter)
	{
		UE_LOG(LogASWeaponSystem, Error,
			   TEXT("Weapon can be used equipped only for character, but insigator %s is not a character"),
			   *GetInstigator()->GetName());
		return;
	}
	
	AttachWeaponToUnequippedSocket();
}

void AWeapon::Equip()
{
	if (!InstigatorCharacter)
	{
		UE_LOG(LogASWeaponSystem, Error,
			   TEXT("Weapon can be used equipped only for character, but insigator %s is not a character"),
			   *GetInstigator()->GetName());
		return;
	}

	InstigatorCharacter->GetMesh()->LinkAnimClassLayers(*AnimationLayer);

	AttachToComponent(InstigatorCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		EquippedSocketName);
}

void AWeapon::Unequip()
{
	if (!InstigatorCharacter)
	{
		UE_LOG(LogASWeaponSystem, Error,
			   TEXT("Weapon can be used unequipped only for character, but insigator %s is not a character"),
			   *GetInstigator()->GetName());
		return;
	}

	InstigatorCharacter->GetMesh()->UnlinkAnimClassLayers(*AnimationLayer);

	AttachWeaponToUnequippedSocket();
}

void AWeapon::AttachWeaponToUnequippedSocket()
{
	AttachToComponent(InstigatorCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		UnequippedSocketName);
}
