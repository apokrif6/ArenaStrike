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

	virtual void ReceiveIncomingGait_Implementation(const EGait IncomingGait) override;

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UASCharacterMovementComponent* GetCharacterMovementComponent() const;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	FLocomotionAnimationData LocomotionData;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SavePivotDataOnPivotStateBecomeRelevant();

private:
	UPROPERTY()
	AASCharacter* OwnerCharacter;

	void UpdateVelocityData();

	void UpdateAccelerationData();

	void UpdateLocationData();

	void UpdateRotationData(const float DeltaSeconds);

	void UpdateOrientationData();

	void UpdateGaitData();

	static ELocomotionDirection CalculateLocomotionDirection(const ELocomotionDirection CurrentLocomotionDirection,
	                                                         const float CurrentLocomotionAngle,
	                                                         const float BackwardMinThreshold,
	                                                         const float BackwardMaxThreshold,
	                                                         const float ForwardMinThreshold,
	                                                         const float ForwardMaxThreshold, const float Deadzone);
};
