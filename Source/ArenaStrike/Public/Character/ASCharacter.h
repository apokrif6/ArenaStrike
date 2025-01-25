// Copyright apokrif6. All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ASCharacter.generated.h"

#pragma region Forward Declarations
class UGameplayAbilitiesInputBindingsDataAsset;
class UCameraComponent;
class USpringArmComponent;
class UWeaponComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
#pragma endregion

DECLARE_LOG_CATEGORY_EXTERN(LogASCharacter, Log, All);

UCLASS(Abstract)
class ARENASTRIKE_API AASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	explicit AASCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimLayersClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SwitchWeaponInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Input")
	TObjectPtr<UGameplayAbilitiesInputBindingsDataAsset> GameplayAbilitiesInputBindings;

private:
	UFUNCTION()
	void OnAbilityInputPressed(int32 InputID);

	UFUNCTION()
	void OnAbilityInputReleased(int32 InputID);

	UFUNCTION()
	void SwitchWeapon(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	void InitializeGameplayAbilitySystem() const;
};
#pragma endregion
