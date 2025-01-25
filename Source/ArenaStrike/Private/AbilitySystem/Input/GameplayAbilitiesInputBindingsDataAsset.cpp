// Copyright apokrif6. All Rights Reserved


#include "AbilitySystem/Input/GameplayAbilitiesInputBindingsDataAsset.h"

#if WITH_EDITOR
void UGameplayAbilitiesInputBindingsDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (const FProperty* Property = PropertyChangedEvent.Property;
		Property && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UGameplayAbilitiesInputBindingsDataAsset,
		                                                            InputAbilities) && !InputAbilities.IsEmpty())
	{
		TArray<FGameplayInputAbilityInfo> InputAbilitiesArray = InputAbilities.Array();
		InputAbilities.Reset();

		for (size_t i = 0; i < InputAbilitiesArray.Num(); ++i)
		{
			FGameplayInputAbilityInfo& Info = InputAbilitiesArray[i];
			Info.InputID = i;
			InputAbilities.Add(Info);
		}
	}
}
#endif
