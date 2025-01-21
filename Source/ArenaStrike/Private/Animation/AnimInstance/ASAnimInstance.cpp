// Copyright apokrif6. All Rights Reserved


#include "ArenaStrike/Public/Animation/AnimInstance/ASAnimInstance.h"

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

UCharacterMovementComponent* UASAnimInstance::GetCharacterMovementComponent() const
{
	if (const ACharacter* OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner()))
	{
		return OwnerCharacter->GetCharacterMovement();
	}

	return nullptr;
}
