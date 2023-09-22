// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Take Control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

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

}

void APlayerCharacter::ImpactOnLand(UMovementComponent* MoveComp)
{
	float vel = abs(MoveComp->Velocity.Z);

	/*
		using a custom bool function to check if player velocity is in range to set landing State.
	*/
	if (inRange(vel, 300, 900)) 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Normal")),
			LandState::NORMAL;
	
	
	
	
	//if (abs(MoveComp->Velocity.Z) >= inRange(300, 900))

	//
	//if (abs(MoveComp->Velocity.Z) >= inRange(300, 900))
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Soft")),
	//	LandState::SOFT;
	//if (abs(MoveComp->Velocity.Z) > 1250)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("LandState Heavy")),
	//	LandState::HEAVY;

}

bool APlayerCharacter::inRange(float Velocity, float X, float Y)
{
	if (Velocity < X && Velocity > Y)
	{
		return true;
	}
	return false;
}

