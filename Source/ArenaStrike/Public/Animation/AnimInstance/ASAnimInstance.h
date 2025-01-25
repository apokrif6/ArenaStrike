// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/Interfaces/ASAnimationInterface.h"
#include "ASAnimInstance.generated.h"

class UASCharacterMovementComponent;
/**
 * Base class for anim blueprints
 */
UCLASS()
class ARENASTRIKE_API UASAnimInstance : public UAnimInstance, public IASAnimationInterface
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
 
protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UASCharacterMovementComponent* GetCharacterMovementComponent() const;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity2D = FVector::ZeroVector;
};
