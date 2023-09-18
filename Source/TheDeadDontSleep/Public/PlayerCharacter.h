// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class THEDEADDONTSLEEP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	//TObjectPtr<UCT_Cmpt_MantleSytem> a; 

#pragma region Player Camera ------------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	bool isRightShoulder;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	UCameraComponent* TPSCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

#pragma endregion
#pragma region Player Components ------------------------------------------
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USceneComponent* Pistol;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UChildActorComponent* PistolChild;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USceneComponent* Rifle;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UChildActorComponent* RifleChild;
	
	// - Weapon System
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	//

	// - Mantle System
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	//
#pragma endregion
#pragma region Player Character ------------------------------------------
	/*
	
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BP_ThirdPersonCharacter")
	TObjectPtr<UTimelineComponent> Aim_Smooth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TPSCharacter");
	TObjectPtr<UTimelineComponent> Slide;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TPSCharacter");
	TObjectPtr<UTimelineComponent> CrouchSmooth;
#pragma endregion
#pragma region Player Movement ------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	double TurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isCrouching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isSprinting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isSliding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isDodging;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	double DodgeForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	double DodgeRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	double Right;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	double Forward;

	//UPROPERTY(EditDefaultsOnly, Category = "Movement")
	//TEnumAsByte<LandState> LandState;

	//UPROPERTY(EditDefaultsOnly, Category = "Movement")
	//... AnimationState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isJumping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isAiming;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//TObjectPtr<UUI_Crosshair_C> UIcrosshair;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isPistolEquip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isRifleEquip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isWeaponEquip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool CanFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool isAttacking;

#pragma endregion
#pragma region Tick & Setup Player Input Component ------------------------------------------
public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion



public:
	UFUNCTION(BlueprintCallable)
	void ImpactOnLand();
};
