// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAssetManager.h"
#include "HeroGameplayTags.h"
#include "AbilitySystemGlobals.h"

UHeroAssetManager& UHeroAssetManager::Get()
{
	check(GEngine);
	UHeroAssetManager* HeroAssetManager = Cast<UHeroAssetManager>(GEngine->AssetManager);
	return *HeroAssetManager;
}

void UHeroAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FHeroGameplayTags::InitializeNativeGameplayTags();
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
