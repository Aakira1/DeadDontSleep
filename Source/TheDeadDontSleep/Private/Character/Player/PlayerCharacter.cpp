#include "Character/Player/PlayerCharacter.h"
#include "Character/Abilities/CharacterSystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

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

#pragma region /---------------------------/
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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
#pragma endregion Tick, BeginPlay, SetupPlayerInputComponent, BindInput
#pragma region /---------------------------/
UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	//needs to return AbilitySystemComponent Object
	return AbilityComponent;
}

void APlayerCharacter::InitializeAttributes()
{
	//Initialize for MP or Co-op here
	return;
}
void APlayerCharacter::InitializeAbilities(TSubclassOf<UGGGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (AbilityComponent->IsValidLowLevelFast())
	{
		if (HasAuthority() && AbilityToGet)
		{
			AbilityComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilityComponent->InitAbilityActorInfo(this, this);
	}
}

int32 APlayerCharacter::GetCharacterLevel() const
{
	return int32();
}
float APlayerCharacter::GetHealth() const
{
	if (!BaseAttributeSetBase)return 0.0f;
	return BaseAttributeSetBase->GetHealth();
}
float APlayerCharacter::GetMaxHealth() const
{
	if (BaseAttributeSetBase->IsValidLowLevelFast())
	{
		return BaseAttributeSetBase->GetMaxHealth();
	} return 0.0f;
}
float APlayerCharacter::GetStamina() const
{
	if (BaseAttributeSetBase->IsValidLowLevelFast())
	{
		return BaseAttributeSetBase->GetStamina();
	} return 0.0f;
}
float APlayerCharacter::GetMaxStamina() const
{
	if (BaseAttributeSetBase->IsValidLowLevelFast())
	{
		return BaseAttributeSetBase->GetMaxStamina();
	} return 0.0f;
}
float APlayerCharacter::GetMoveSpeed() const
{
	if (BaseAttributeSetBase->IsValidLowLevelFast())
	{
		return BaseAttributeSetBase->GetMoveSpeed();
	} return 0.0f;
}
float APlayerCharacter::GetMoveSpeedBaseValue() const
{
	if (BaseAttributeSetBase->IsValidLowLevelFast()) {
		return BaseAttributeSetBase->GetMoveSpeedAttribute().GetGameplayAttributeData(BaseAttributeSetBase)->GetBaseValue();
	} return 0.0f;
}

bool APlayerCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}
void APlayerCharacter::Die()
{
	//Remove items
	return;
}
void APlayerCharacter::FinishDying()
{
	return;
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

#pragma region /---------------------------/
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
void APlayerCharacter::IsSprinting()
{
	// boolean for isSprinting set to true
	isSprinting = true;

	// Max walk speed set to desired speed to match function requirements.
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
void APlayerCharacter::StopSprinting()
{
	// boolean for isSprinting set to false
	isSprinting = false;

	// Max walk speed set to desired speed to match function requirements.
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}
#pragma endregion Player Movement
