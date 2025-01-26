// Copyright apokrif6. All Rights Reserved


#include "AbilitySystem/Abilities/Weapon/SwitchWeaponAbility.h"

#include "InputActionValue.h"
#include "Character/ASCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/WeaponComponent.h"

void USwitchWeaponAbility::OnTriggeredInputAction(const FInputActionValue& Value)
{
	const AASCharacter* Character = Cast<AASCharacter>(GetAvatarActorFromActorInfo());
	if (!Character)
	{
		return;
	}

	UWeaponComponent* WeaponComponent = Character->GetComponentByClass<UWeaponComponent>();
	if (!WeaponComponent)
	{
		return;
	}


	const int TruncatedValue = UKismetMathLibrary::FTrunc(Value.Get<float>());

	//TODO
	//create better implementation
	//maybe cast int to uenum?
	EEquippedWeapon NewWeapon;
	switch (TruncatedValue)
	{
	case 1:
		NewWeapon = EEquippedWeapon::Unarmed;
		break;
	case 2:
		NewWeapon = EEquippedWeapon::Pistol;
		break;
	case 3:
		NewWeapon = EEquippedWeapon::Rifle;
		break;
	default:
		NewWeapon = EEquippedWeapon::Unarmed;
	}

	WeaponComponent->EquipWeapon(NewWeapon);

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
