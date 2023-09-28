// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Take Control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Player Impact Height Determination
	ImpactOnLand();
	
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::PlayerSlide()
{
	

	if (GetVelocity().Length() > 500 && ACharacter::CanJump())
	{
		isSliding = true;

		if (isWeaponEquip)
		{
			if (DoOnce.Execute())
			{
				Crouch();
				Character->PlayAnimMontage(SlideMontage, 1.0, "None");
				//switch (GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::PlayerSlide, 1.0, "None"), 0.5, false)
				//{
				//case 0:
				//	UnCrouch();
				//	//CeilingTrace();
				//case 1:
				//	return;
				//}
			}
		}
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
	//FString Message = FString::Printf(TEXT("BeginPlay of %s - Location: %s"),
	//	*(GetName()), *(GetActorLocation().ToString()));

	if (GEngine)
	{
		/*Debugging Purpose Only*/
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, Message);
		
		if (!abs(Z) >= 1 && !abs(Z) <= 500)
		{
			GetActorLocation().Z;
			
			/*Debuggin Purpose Only*/
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Normal"));
			
			LandingState::NORMAL;
		}
		if (!abs(Z) >= 501 && !abs(Z) <= 900)
		{
			GetActorLocation().Z;
			
			/*Debuggin Purpose Only*/
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Soft"));
			
			LandingState::SOFT;
		}
		if (!abs(Z) > 901 || !abs(Z) == 0) {
			GetActorLocation().Z;

			/*Debugging Purpose Only*/
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Soft"));
			
			LandingState::HEAVY;
		}
	}
}




