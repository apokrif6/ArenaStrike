// Copyright apokrif6. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Gait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ASCharacterMovementComponent.generated.h"


enum class EGait : uint8;

UCLASS(ClassGroup=("Movement"), meta=(BlueprintSpawnableComponent))
class ARENASTRIKE_API UASCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UASCharacterMovementComponent();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetGait(const EGait InGait);

	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (BlueprintThreadSafe))
	EGait GetGait() const { return CurrentGait; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	TMap<EGait, FGaitSettings> GaitSettings;

	virtual void BeginPlay() override;

private:
	EGait CurrentGait = EGait::Walking;
};
