// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HeroCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/HeroOverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "HEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class GAS_PRO_API AHEnemy : public AHeroCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AHEnemy();
	
	/** 敌人接口 **/
	virtual void HighLightActor() override;
	virtual void UnHighLightActor()override;
	/** 结束接口 **/
	
	/** Combat接口 **/
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	/** 结束接口 **/

	UPROPERTY(BlueprintAssignable)
	FOnAattributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAattributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	float LifeSpan = 5.f;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
