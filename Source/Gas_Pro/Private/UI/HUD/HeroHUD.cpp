// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HeroHUD.h"

#include "UI/Widget/HeroUserWidget.h"
#include "UI/WidgetController/HeroOverlayWidgetController.h"

UHeroOverlayWidgetController* AHeroHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UHeroOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributesMenuWidgetController* AHeroHUD::GetAttributesMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributesMenuWidgetController == nullptr)
	{
		AttributesMenuWidgetController = NewObject<UAttributesMenuWidgetController>(this, AttributesMenuWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return AttributesMenuWidgetController;
}

void AHeroHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class 未初始化，请在BP_HeroHUD中设置"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class 未初始化，请在BP_HeroHUD中设置"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UHeroUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UHeroOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

