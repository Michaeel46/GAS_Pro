// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HeroAbilitySystemLibrary.generated.h"

class UAttributesMenuWidgetController;
class UAbilitySystemComponent;
class UHeroOverlayWidgetController;
/**
 * 
 */
UCLASS()
class GAS_PRO_API UHeroAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintpure, Category = "HeroAbilitySystemLibrary|WidgetController")
	static UHeroOverlayWidgetController* GetHeroOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(Blueprintpure, Category = "HeroAbilitySystemLibrary|WidgetController")
	static UAttributesMenuWidgetController* GetAttributesMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "HeroAbilitySystemLibrary | CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level , UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "HeroAbilitySystemLibrary | CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "HeroAbilitySystemLibrary | CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
};
