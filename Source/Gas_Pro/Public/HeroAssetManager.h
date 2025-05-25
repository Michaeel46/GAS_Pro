// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HeroAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_PRO_API UHeroAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UHeroAssetManager& Get();

	protected:
	virtual void StartInitialLoading() override;
};
