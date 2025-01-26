// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ASGameplayAbility.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ARENASTRIKE_API UASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	explicit UASGameplayAbility(const FObjectInitializer& ObjectInitializer);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bCancelAbilityOnInputReleased = false;

	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	TArray<uint32> TriggeredEventHandles;

	virtual void OnTriggeredInputAction(const FInputActionValue& Value)
	{
	}
};
