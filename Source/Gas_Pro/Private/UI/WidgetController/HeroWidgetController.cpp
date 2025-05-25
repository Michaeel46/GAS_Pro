// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/HeroWidgetController.h"

void UHeroWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WcParams)
{
	PlayerController = WcParams.PlayerController;
	PlayerState = WcParams.PlayerState;
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
}

void UHeroWidgetController::BroadcastInitialValues()
{
	
}

void UHeroWidgetController::BindCallbacksToDependencies()
{
	
}
