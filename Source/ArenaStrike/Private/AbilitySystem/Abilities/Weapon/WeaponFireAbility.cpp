// Copyright apokrif6. All Rights Reserved


#include "AbilitySystem/Abilities/Weapon/WeaponFireAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponComponent.h"

void UWeaponFireAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	const AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("WeaponFireAbility: AvatarActor is null!"));
		return;
	}
	
	PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, FName("WeaponFireAbility"), InstigatorFireAnimMontage.Get(), 1);
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);

	const UWeaponComponent* AvatarActorWeaponComponent = AvatarActor->GetComponentByClass<UWeaponComponent>();
	if (!AvatarActorWeaponComponent)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("WeaponFireAbility: AvatarActor is null!"));
		return;
	}

	PlayMontageAndWait->ReadyForActivation();

	const AWeapon* AvatarActorEquippedWeapon = AvatarActorWeaponComponent->GetEquippedWeapon();
	if (!AvatarActorEquippedWeapon)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("WeaponFireAbility: AvatarActorEquippedWeapon is null!"));
		return;
	}

	AvatarActorEquippedWeapon->GetSkeletalMeshComponent()->PlayAnimation(WeaponFireAnimSequence, false);
}

void UWeaponFireAbility::OnMontageCancelled()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
}

void UWeaponFireAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
