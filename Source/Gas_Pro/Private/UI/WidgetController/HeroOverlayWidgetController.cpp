// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/HeroOverlayWidgetController.h"

#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "AbilitySystem/HeroAttributeSet.h"

void UHeroOverlayWidgetController::BroadcastInitialValues()
{
	const UHeroAttributeSet* HeroAttributeSet = CastChecked<UHeroAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(HeroAttributeSet->GetHealth());  
	OnMaxHealthChanged.Broadcast(HeroAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(HeroAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(HeroAttributeSet->GetMaxMana());
}

void UHeroOverlayWidgetController::BindCallbacksToDependencies()
{
	const UHeroAttributeSet* HeroAttributeSet = CastChecked<UHeroAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UHeroAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				//如果Tag = Message.HealthPotion
				//"Message.HealthPotion".MatchesTag("Message")返回true, "Message".MatchesTag("Message.HealthPotion")返回flase
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if (Row != nullptr)
					{
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		}
	);
}

