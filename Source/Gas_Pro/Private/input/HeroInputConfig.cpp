// Fill out your copyright notice in the Description page of Project Settings.


#include "input/HeroInputConfig.h"

const UInputAction* UHeroInputConfig::FindAbilityInputActionforTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FHeroInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Tag [%s] on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
