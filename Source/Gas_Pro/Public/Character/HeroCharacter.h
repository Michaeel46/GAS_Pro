// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HeroCharacterBase.h"
#include "TimerManager.h"
#include "HeroCharacter.generated.h"


/**
 * 
 */
UCLASS()
class GAS_PRO_API AHeroCharacter : public AHeroCharacterBase
{
	GENERATED_BODY()
public:
	AHeroCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/** Combat接口 获取Level**/
	virtual int32 GetPlayerLevel() override;

	
private:
	virtual void InitAbilityActorInfo() override;
	FTimerHandle TimerHandle_InitAbilityActorInfo; // 声明定时器句柄
};
