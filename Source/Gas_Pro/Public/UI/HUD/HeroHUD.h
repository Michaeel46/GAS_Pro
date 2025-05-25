// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AttributesMenuWidgetController.h"

#include "HeroHUD.generated.h"

class UHeroOverlayWidgetController;
class UHeroUserWidget;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class GAS_PRO_API AHeroHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UHeroOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UAttributesMenuWidgetController* GetAttributesMenuWidgetController(const FWidgetControllerParams& WCParams); 	

	void InitOverlay(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UHeroUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHeroUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UHeroOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHeroOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributesMenuWidgetController> AttributesMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributesMenuWidgetController> AttributesMenuWidgetControllerClass;
};
