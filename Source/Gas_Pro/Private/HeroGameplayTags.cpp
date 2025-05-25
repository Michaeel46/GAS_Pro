// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroGameplayTags.h"
#include "GameplayTagsManager.h"

FHeroGameplayTags FHeroGameplayTags::GameplayTags;

void FHeroGameplayTags::InitializeNativeGameplayTags()
{
    // 主要属性
    GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Strength"),
        FString("Increases physical damage and carrying capacity")
    );
    
    GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Intelligence"),
        FString("Increases magical damage and mana capacity")
    );
    
    GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Resilience"),
        FString("Increases armor and resistance to status effects")
    );
    
    GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Vigor"),
        FString("Increases maximum health and health regeneration")
    );

    // 次要属性
    GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.Armor"),
        FString("Reduce damage taken, improve Block Chance")
    );
    
    GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.ArmorPenetration"),
        FString("Ignore a percentage of target's armor")
    );
    
    GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.BlockChance"),
        FString("Chance to block incoming attacks")
    );
    
    GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitChance"),
        FString("Chance to deal critical damage")
    );
    
    GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitDamage"),
        FString("Multiplier for critical hits")
    );
    
    GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitResistance"),
        FString("Reduce chance of being critically hit")
    );
    
    GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.HealthRegeneration"),
        FString("Amount of health regenerated per second")
    );
    
    GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.ManaRegeneration"),
        FString("Amount of mana regenerated per second")
    );
    
    GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxHealth"),
        FString("Maximum health capacity")
    );
    
    GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxMana"),
        FString("Maximum mana capacity")
    );

    // 输入属性
    GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.LMB"),
        FString("Input Tag for Left Mouse Button")
    );

    GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.RMB"),
        FString("Input Tag for Right Mouse Button")
    );

    GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.1"),
        FString("Input Tag for 1 key")
    );

    GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.2"),
     FString("Input Tag for 2 key")
    );

    GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.3"),
        FString("Input Tag for 3 key")
    );

    GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.4"),
        FString("Input Tag for 4 key")
    );

    GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Damage"),
        FString("Damage")
    );

    GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Effects.HitReact"),
        FString("Tag granted when Hit Reacting")
    );
}
