// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class LandState : uint8 {
	NORMAL = 0	UMETA(DisplayName = "Normal"),
	SOFT = 1	UMETA(DisplayName = "Soft"),
	HEAVY = 2	UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class AnimState : uint8 {
	UNARMED = 0	UMETA(DisplayName = "Unarmed"),
	PISTOL = 1	UMETA(DisplayName = "Pistol"),
	RIFLE =	2	UMETA(DisplayName = "Rifle")
};

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
#pragma region Player Camera ------------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	bool isRightShoulder;

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
	LandState PLandingState;

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

public:
#pragma region Tick & Setup Player Input Component ------------------------------------------

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

	UFUNCTION()
	void ImpactOnLand(UMovementComponent* MoveComp);

	bool inRange(float, float, float);
};
