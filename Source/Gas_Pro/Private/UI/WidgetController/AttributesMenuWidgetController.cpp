// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributesMenuWidgetController.h"

#include "HeroGameplayTags.h"
#include "AbilitySystem/HeroAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributesMenuWidgetController::BindCallbacksToDependencies()
{
	UHeroAttributeSet* AS = Cast<UHeroAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributesMenuWidgetController::BroadcastInitialValues()
{
	UHeroAttributeSet* AS = Cast<UHeroAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributesMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FHeroAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
