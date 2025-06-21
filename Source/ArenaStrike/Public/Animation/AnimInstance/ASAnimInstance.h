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

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetRootYawOffsetMode(const ERootYawOffsetMode RootYawOffsetMode);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetTurnInPlaceDirection(const ETurnInPlaceDirection TurnInPlaceDirection);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	float UpdateTurnInPlaceAnimationTime(const float DeltaSeconds);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void ResetTurnInPlaceAnimationTime();

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetFinalTurnInPlaceAnimation(UAnimSequence* FinalTurnInPlaceAnimation);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void ProcessTurnInPlaceYawCurve();

	/**
	 * Normalizes axis of the root yaw offset and set it
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetRootYawOffset(const float Angle);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Curves")
	FName DisableLHandIKCurveName = "DisableLHandIK";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Curves")
	FName IsTurningCurveName = "IsTurning";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Curves")
	FName TurnInPlaceYawCurveName = "root_rotation_Z";

private:
	UPROPERTY()
	AASCharacter* OwnerCharacter;

	void UpdateVelocityData();

	void UpdateAccelerationData();

	void UpdateLocationData();

	void UpdateRotationData(const float DeltaSeconds);

	void UpdateRootYawOffsetData(const float DeltaSeconds);

	void UpdateOrientationData();

	void UpdateGaitData();

	static ELocomotionDirection CalculateLocomotionDirection(const ELocomotionDirection CurrentLocomotionDirection,
	                                                         const float CurrentLocomotionAngle,
	                                                         const float BackwardMinThreshold,
	                                                         const float BackwardMaxThreshold,
	                                                         const float ForwardMinThreshold,
	                                                         const float ForwardMaxThreshold, const float Deadzone);
};
