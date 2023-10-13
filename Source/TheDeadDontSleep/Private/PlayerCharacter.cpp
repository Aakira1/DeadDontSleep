// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Character/Abilities/CharacterSystemComponent.h"



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
	
	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>("Attributes");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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


UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	//needs to return AbilitySystemComponent Object
	return AbilityComponent;
}

void APlayerCharacter::InitializeAbilities()
{
	// Give Abilities, Server Only
	if (!HasAuthority() || !AbilityComponent) return;

	for (TSubclassOf<UGGGameplayAbility>& Ability : DefaultAbilities)
	{
		//this will determine based on the players level when to give the ability
		AbilityComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 
			static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}
}

void APlayerCharacter::InitializeEffects()
{
	if (!AbilityComponent) return;

	FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& Effect : DefaultEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}



void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!AbilityComponent) return;

	AbilityComponent->InitAbilityActorInfo(this, this);

	InitializeAbilities();
	InitializeEffects();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!AbilityComponent) return;

	AbilityComponent->InitAbilityActorInfo(this, this);

	BindInput();

	InitializeEffects();
}

void APlayerCharacter::BindInput()
{
	if (bIsInputBound || !AbilityComponent || !IsValid(InputComponent)) return;

	FTopLevelAssetPath EnumAssetPath = FTopLevelAssetPath(FName("/Script/TheDeadDontSleep"), FName("EAbilityInputID"));
	AbilityComponent->BindAbilityActivationToInputComponent(
		InputComponent, FGameplayAbilityInputBinds(FString("Confirm"), FString("Cancel"),
			EnumAssetPath, static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));

	bIsInputBound = true;
}


//Start & Stop the Players sprinting 
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




