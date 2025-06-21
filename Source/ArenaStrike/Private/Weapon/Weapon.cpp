// Copyright apokrif6. All Rights Reserved


#include "Weapon/Weapon.h"

#include "AbilitySystemComponent.h"
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
	//TODO
	//should store UGameplayAbilitiesInputBindingsDataAsset to bind weapon abilities to input actions in runtime
	
	if (!InstigatorCharacter)
	{
		UE_LOG(LogASWeaponSystem, Error,
			   TEXT("Weapon can be used equipped only for character, but insigator %s is not a character"),
			   *GetInstigator()->GetName());
		return;
	}

	if (UAbilitySystemComponent* InstigatorAbilitySystemComponent = InstigatorCharacter->GetComponentByClass<UAbilitySystemComponent>();
		InstigatorAbilitySystemComponent && EquippedWeaponGameplayEffectToApplyToInstigator)
	{
		EquippedWeaponGameplayEffectHandle = InstigatorAbilitySystemComponent->ApplyGameplayEffectToSelf(
			EquippedWeaponGameplayEffectToApplyToInstigator->GetDefaultObject<UGameplayEffect>(),
			1.0f, InstigatorAbilitySystemComponent->MakeEffectContext());
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

	if (UAbilitySystemComponent* InstigatorAbilitySystemComponent = InstigatorCharacter->GetComponentByClass<UAbilitySystemComponent>();
		InstigatorAbilitySystemComponent && EquippedWeaponGameplayEffectHandle.IsValid())
	{
		InstigatorAbilitySystemComponent->RemoveActiveGameplayEffect(EquippedWeaponGameplayEffectHandle);
	}

	InstigatorCharacter->GetMesh()->UnlinkAnimClassLayers(*AnimationLayer);

	AttachWeaponToUnequippedSocket();
}

void AWeapon::AttachWeaponToUnequippedSocket()
{
	AttachToComponent(InstigatorCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		UnequippedSocketName);
}
