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

	AbilityComponent = CreateDefaultSubobject<UCharacterSystemComponent>("Ability System Component");
	AbilityComponent->SetIsReplicated(true);
	AbilityComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>("Attributes");
}


UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	//needs to return AbilitySystemComponent Object
	return AbilityComponent;
}

UGDAttributeSetBase* APlayerCharacter::GetAttributeSetBase() const
{
	return nullptr;
}

void APlayerCharacter::InitializeAttributes()
{
	if (AbilityComponent /*&& DefaultAttributeEffect*/) {

	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilityComponent)
	{
		AbilityComponent->InitAbilityActorInfo(this, this);
	}

	// ASC mixemode replication requires that the ASC owner's owner be the controller
	SetOwner(NewController);
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




