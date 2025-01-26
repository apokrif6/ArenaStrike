// Copyright apokrif6. All Rights Reserved


#include "AbilitySystem/Abilities/ASGameplayAbility.h"

#include "EnhancedInputComponent.h"
#include "AbilitySystem/Input/GameplayAbilitiesInputBindingsDataAsset.h"
#include "Character/ASCharacter.h"

UASGameplayAbility::UASGameplayAbility(const FObjectInitializer& ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UASGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bool bSuccess = false;

	if (const AASCharacter* Character = Cast<AASCharacter>(GetAvatarActorFromActorInfo()))
	{
		EnhancedInputComponent = Cast<UEnhancedInputComponent>(Character->InputComponent);
		if (EnhancedInputComponent)
		{
			if (const UGameplayAbilitiesInputBindingsDataAsset* PlayerGameplayAbilitiesDataAsset = Character->
				GetGameplayAbilitiesInputBindings())
			{
				for (const auto& InputAbility : PlayerGameplayAbilitiesDataAsset->GetInputAbilities())
				{
					if (InputAbility.IsValid() && InputAbility.GameplayAbilityClass == GetClass())
					{
						FEnhancedInputActionEventBinding& TriggeredEventBinding = EnhancedInputComponent->
							BindAction(InputAbility.InputAction, ETriggerEvent::Triggered, this,
							           &ThisClass::OnTriggeredInputAction);
						const uint32 TriggeredEventHandle = TriggeredEventBinding.GetHandle();

						TriggeredEventHandles.AddUnique(TriggeredEventHandle);

						bSuccess = true;
					}
				}
			}
		}
	}

	if (bSuccess)
	{
		CommitAbility(Handle, ActorInfo, ActivationInfo);
	}
	else
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UASGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                    bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (EnhancedInputComponent)
	{
		for (const uint32 EventHandle : TriggeredEventHandles)
		{
			EnhancedInputComponent->RemoveBindingByHandle(EventHandle);
		}

		EnhancedInputComponent = nullptr;
	}

	TriggeredEventHandles.Reset();
}

void UASGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	if (bCancelAbilityOnInputReleased)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}
