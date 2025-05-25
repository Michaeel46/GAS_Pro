// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HeroCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/HeroPlayerController.h"
#include "Player/HeroPlayerState.h"
#include "UI/HUD/HeroHUD.h"

AHeroCharacter::AHeroCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitAbilityActorInfo();
}

void AHeroCharacter::InitAbilityActorInfo()
{
	AHeroPlayerState* HeroPlayerState= GetPlayerState<AHeroPlayerState>();
	if (!HeroPlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("HeroPlayerState is null. Will try again later."));
		GetWorldTimerManager().SetTimer(TimerHandle_InitAbilityActorInfo, this, &AHeroCharacter::InitAbilityActorInfo, 1.0f, false);
		return;
	}
	check(HeroPlayerState);
	HeroPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(HeroPlayerState, this);
	Cast<UHeroAbilitySystemComponent>(HeroPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = HeroPlayerState->GetAbilitySystemComponent();
	AttributeSet = HeroPlayerState->GetAttributeSet();

	if (AHeroPlayerController* HeroPlayerController = Cast<AHeroPlayerController>(GetController()))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(HeroPlayerController->GetHUD()))
		{
			HeroHUD->InitOverlay(HeroPlayerController, HeroPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}

int32 AHeroCharacter::GetPlayerLevel()
{
	const AHeroPlayerState* HeroPlayerState= GetPlayerState<AHeroPlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->GetPlayerLevel();
}