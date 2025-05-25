// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/HeroUserWidget.h"

void UHeroUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
