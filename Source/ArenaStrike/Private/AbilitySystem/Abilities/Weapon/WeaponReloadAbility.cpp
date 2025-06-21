// Copyright apokrif6. All Rights Reserved


#include "AbilitySystem/Abilities/Weapon/WeaponReloadAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponComponent.h"

void UWeaponReloadAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("UWeaponReloadAbility: AvatarActor is null!"));
		return;
	}
	
	PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, FName("WeaponReloadAbility"), InstigatorReloadAnimMontage.Get(), 1);
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);

	const UWeaponComponent* AvatarActorWeaponComponent = AvatarActor->GetComponentByClass<UWeaponComponent>();
	if (!AvatarActorWeaponComponent)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("UWeaponReloadAbility: AvatarActor is null!"));
		return;
	}

	PlayMontageAndWait->ReadyForActivation();

	const AWeapon* AvatarActorEquippedWeapon = AvatarActorWeaponComponent->GetEquippedWeapon();
	if (!AvatarActorEquippedWeapon)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("UWeaponReloadAbility: AvatarActorEquippedWeapon is null!"));
		return;
	}

	AvatarActorEquippedWeapon->GetSkeletalMeshComponent()->PlayAnimation(WeaponReloadAnimSequence, false);
}

void UWeaponReloadAbility::OnMontageCancelled()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
}

void UWeaponReloadAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
