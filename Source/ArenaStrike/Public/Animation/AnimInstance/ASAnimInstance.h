// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/Locomotion/LocomotionAnimationData.h"
#include "Animation/Interfaces/ASAnimationInterface.h"
#include "ASAnimInstance.generated.h"

class AASCharacter;
class UASCharacterMovementComponent;
/**
 * Base class for anim blueprints
 */
UCLASS()
class ARENASTRIKE_API UASAnimInstance : public UAnimInstance, public IASAnimationInterface
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UASCharacterMovementComponent* GetCharacterMovementComponent() const;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	FLocomotionAnimationData LocomotionData;

private:
	UPROPERTY()
	AASCharacter* OwnerCharacter;

	void GetVelocityData();

	void GetRotationData(const float DeltaSeconds);

	void UpdateOrientationData();

	static ELocomotionDirection CalculateLocomotionDirection(const ELocomotionDirection CurrentLocomotionDirection,
	                                                         const float CurrentLocomotionAngle,
	                                                         const float BackwardMinThreshold,
	                                                         const float BackwardMaxThreshold,
	                                                         const float ForwardMinThreshold,
	                                                         const float ForwardMaxThreshold, const float Deadzone);
};
