// Copyright apokrif6. All Rights Reserved


#include "ArenaStrike/Public/Animation/AnimInstance/ASAnimInstance.h"

#include "Character/Movement/ASCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UASAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!TryGetPawnOwner())
	{
		return;
	}

	Velocity = GetCharacterMovementComponent()->Velocity;
	Velocity2D = Velocity * FVector{1.f, 1.f, 0.f};
}

UASCharacterMovementComponent* UASAnimInstance::GetCharacterMovementComponent() const
{
	if (const ACharacter* OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner()))
	{
		return Cast<UASCharacterMovementComponent>(OwnerCharacter->GetCharacterMovement());
	}

	return nullptr;
}
