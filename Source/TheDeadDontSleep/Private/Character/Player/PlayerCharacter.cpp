// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/PlayerCharacter.h"
#include "Character/Abilities/CharacterSystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Take Control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Ability System Component Initialized 
	AbilityComponent = CreateDefaultSubobject<UCharacterSystemComponent>("Ability System Component");
	AbilityComponent->SetIsReplicated(true);
	AbilityComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	//AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>("Attributes");
}
/*---------------------------*/#pragma region Begin, Tick, SPIC
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilityComponent)
	{
		BaseAttributeSetBase = AbilityComponent->GetSet<UCharacterAttributeSetBase>();

		AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetBase->GetHealthAttribute()).AddUObject(this, &APlayerCharacter::OnHealthChangedNative);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetBase->GetStaminaAttribute()).AddUObject(this, &APlayerCharacter::OnStaminaChangedNative);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetBase->GetMentalHealthAttribute()).AddUObject(this, &APlayerCharacter::OnMentalChangedNative);
		//const_cast<UCharacterAttributeSetBase*>(BaseAttributeSetBase)->SpeedChangeDelegate.AddDynamic(this, &ABaseCharacter::OnSpeedChangeNative);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*
		Setup Action Bindings Here
	*/
	

	BindInput();
}
void APlayerCharacter::BindInput()
{
}
#pragma endregion Begin, Tick, SPIC
/*---------------------------*/#pragma region GAS System
// Obtains the Ability system to get attributes etc.
UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	//needs to return AbilitySystemComponent Object
	return AbilityComponent;
}

// Initializes the Abilities in the blueprint side
void APlayerCharacter::InitializeAbilities(TSubclassOf<UGGGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (AbilityComponent)
	{
		if (HasAuthority() && AbilityToGet)
		{
			AbilityComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilityComponent->InitAbilityActorInfo(this, this);
	}
}

// currently produce zero value return
void APlayerCharacter::GetHealthValues(float& Health, float& MaxHealth)
{
	if (BaseAttributeSetBase)
	{
		Health = BaseAttributeSetBase->GetHealth();
		MaxHealth = BaseAttributeSetBase->GetMaxHealth();
	}
}
void APlayerCharacter::GetStaminaValues(float& Stamina, float& MaxStamina)
{
	if (BaseAttributeSetBase)
	{
		Stamina = BaseAttributeSetBase->GetStamina();
		MaxStamina = BaseAttributeSetBase->GetMaxStamina();
	}
}
void APlayerCharacter::GetMentalHealthValues(float& Mental, float& MaxMental)
{
	if (BaseAttributeSetBase)
	{
		Mental = BaseAttributeSetBase->GetMentalHealth();
		MaxMental = BaseAttributeSetBase->GetMaxMentalHealth();
	}
}

// Sets Players Health if you wish to us a component health system
void APlayerCharacter::SetHealthValues(float NewHealth, float NewMaxHealth)
{
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetHealthAttribute(), EGameplayModOp::Override, NewHealth);
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetMaxHealthAttribute(), EGameplayModOp::Override, NewMaxHealth);
}
void APlayerCharacter::SetStaminaValues(float NewStamina, float NewMaxStamina)
{
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetHealthAttribute(), EGameplayModOp::Override, NewStamina);
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetHealthAttribute(), EGameplayModOp::Override, NewMaxStamina);
}
void APlayerCharacter::SetMentalHealthValues(float NewMentalH, float NewMaxMentalH)
{
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetHealthAttribute(), EGameplayModOp::Override, NewMentalH);
	AbilityComponent->ApplyModToAttribute(BaseAttributeSetBase->GetHealthAttribute(), EGameplayModOp::Override, NewMaxMentalH);
}

// Is called to any changes to players attributes.
void APlayerCharacter::OnHealthChangedNative(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}
void APlayerCharacter::OnStaminaChangedNative(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged(Data.OldValue, Data.NewValue);
}
void APlayerCharacter::OnMentalChangedNative(const FOnAttributeChangeData& Data)
{
	OnMentalChanged(Data.OldValue, Data.NewValue);
}

#pragma endregion GAS System
/*---------------------------*/#pragma region Player Movement
//Start & Stop the Players sprinting 
void APlayerCharacter::IsSprinting()
{
	// boolean for isSprinting set to true
	isSprinting = true;

	// Max walk speed set to desired speed to match function requirements.
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
//
void APlayerCharacter::StopSprinting()
{
	// boolean for isSprinting set to false
	isSprinting = false;

	// Max walk speed set to desired speed to match function requirements.
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}
//Determines Players Height on Z velocity to add animation state of landing impact.
void APlayerCharacter::ImpactOnLand()
{
	// Get Actor Z Location
	float Z = GetActorLocation().Z;

	/*Debugging Purpose Only*/
	FString Message = FString::Printf(TEXT("BeginPlay of %s - Location: %s"),
		*(GetName()), *(GetActorLocation().ToString()));

	if (GEngine)
	{
		/*Debugging Purpose Only*/
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, Message);

		if ((abs(Z) >= 1) == true && (abs(Z) <= 500) == true)
		{
			/*Debuggin Purpose Only*/
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("True"));
			LandingState::NORMAL;
		}
		if ((abs(Z) >= 501) == true && (abs(Z) <= 900) == true)
		{
			/*Debuggin Purpose Only*/
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Soft"));

			LandingState::SOFT;
		}
		if ((abs(Z) > 1250) == true)
		{
			/*Debugging Purpose Only*/
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Soft"));

			LandingState::HEAVY;
		}
	}
}
#pragma endregion Player Movement and Landing Mechanics