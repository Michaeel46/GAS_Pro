// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HeroAbilitySystemLibrary.h"

#include "Game/HeroGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/HeroWidgetController.h"
#include "Player/HeroPlayerState.h"
#include "UI/HUD/HeroHUD.h"

UHeroOverlayWidgetController* UHeroAbilitySystemLibrary::GetHeroOverlayWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(PC->GetHUD()))
		{
			AHeroPlayerState* PS = PC->GetPlayerState<AHeroPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return HeroHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributesMenuWidgetController* UHeroAbilitySystemLibrary::GetAttributesMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(PC->GetHUD()))
		{
			AHeroPlayerState* PS = PC->GetPlayerState<AHeroPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return HeroHUD->GetAttributesMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UHeroAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AHeroGameModeBase* HeroGameMode = Cast<AHeroGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (HeroGameMode == nullptr) return;

	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefault(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	VitalAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}

void UHeroAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	AHeroGameModeBase* HeroGameMode = Cast<AHeroGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (HeroGameMode == nullptr) return ;
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass , 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UHeroAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AHeroGameModeBase* HeroGameMode = Cast<AHeroGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (HeroGameMode == nullptr) return nullptr;

	return HeroGameMode->CharacterClassInfo;
}
