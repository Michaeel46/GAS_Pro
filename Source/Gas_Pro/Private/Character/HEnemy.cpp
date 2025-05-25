// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HEnemy.h"

#include "HeroGameplayTags.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "AbilitySystem/HeroAbilitySystemLibrary.h"
#include "AbilitySystem/HeroAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gas_Pro/Gas_Pro.h"
#include "UI/Widget/HeroUserWidget.h"

AHEnemy::AHEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UHeroAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UHeroAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AHEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon1->SetRenderCustomDepth(true);
	Weapon1->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AHEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	Weapon1->SetRenderCustomDepth(false);
}

int32 AHEnemy::GetPlayerLevel()
{
	return Level;
}

void AHEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AHEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	UHeroAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	
	if (UHeroUserWidget* HeroUserWidget = Cast<UHeroUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HeroUserWidget->SetWidgetController(this);
	}
	
	if (UHeroAttributeSet* HeroAS = CastChecked<UHeroAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HeroAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FHeroGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AHEnemy::HitReactTagChanged
		);
		OnHealthChanged.Broadcast(HeroAS->GetHealth());
		OnMaxHealthChanged.Broadcast(HeroAS->GetMaxHealth());
	}

}

void AHEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AHEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UHeroAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AHEnemy::InitializeDefaultAttributes() const
{
	UHeroAbilitySystemLibrary::InitializeDefaultAttributes(this , CharacterClass , Level , AbilitySystemComponent);
}
