


#include "Character/HeroCharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gas_Pro/Gas_Pro.h"

AHeroCharacterBase::AHeroCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()-> SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Weapon1 = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon1");
	Weapon1->SetupAttachment(GetMesh(), FName("WeaponHandSocket1"));
	Weapon1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AHeroCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AHeroCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AHeroCharacterBase::Die()
{
	if (Weapon)
	{
		Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	if (Weapon1)
	{
		Weapon1->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	MulticastHandleDeath();
}

void AHeroCharacterBase::MulticastHandleDeath_Implementation()
{
	if (Weapon)
	{
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
	if (Weapon1)
	{
		Weapon1->SetSimulatePhysics(true);
		Weapon1->SetEnableGravity(true);
		Weapon1->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

void AHeroCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AHeroCharacterBase::GetCombatSocketLocation()
{
	if (Weapon)
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	else if (Weapon1)
	{
		return Weapon1->GetSocketLocation(WeaponTipSocketName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid weapon found!"));
		return FVector::ZeroVector;
	}
}

void AHeroCharacterBase::InitAbilityActorInfo()
{
}

void AHeroCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass , Level ,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AHeroCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AHeroCharacterBase::AddCharacterAbilities()
{
	UHeroAbilitySystemComponent* HeroASC = CastChecked<UHeroAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	HeroASC->AddCharacterAbilities(StartupAbilities);
}

void AHeroCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		if (Weapon)
		{
			Weapon->SetMaterial(0, DynamicMatInst);		
		}
		if (Weapon1)
		{
			Weapon1->SetMaterial(0, DynamicMatInst);		
		}
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

