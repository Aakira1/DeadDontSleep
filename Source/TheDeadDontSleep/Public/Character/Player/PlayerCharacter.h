// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
//#include "AbilitySystemInterface.h"
#include "Engine.h" 
#include "CustomFunctions/DoOnce.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include <Character/Abilities/AttributeSets/CharacterAttributeSetBase.h>
#include <Character/Abilities/GameplayAbilities/GGGameplayAbility.h>
#include "PlayerCharacter.generated.h"

#pragma region UENUMS
UENUM(BlueprintType)
enum class LandingState : uint8 {
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
#pragma endregion Likley To moved to a data set

class UCharacterAttributeSetBase;

UCLASS()
class APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

/*---------------------------------*/#pragma region Special Functions
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BindInput();
	bool bIsInputBound{ false };

#pragma endregion Tick, Input, Begin
/*---------------------------------*/#pragma region GAS Ability system
public:
	/****************
	* Ability System
	*****************/
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "GAS|Ability Component")
	void InitializeAbilities(TSubclassOf<UGGGameplayAbility> AbilityToGet, int32 AbilityLevel);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS|Ability Component")
	class UCharacterSystemComponent* AbilityComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS|Ability Attributes")
	const class UCharacterAttributeSetBase* BaseAttributeSetBase;

#pragma region Attribute Variables/Functions
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
	void GetHealthValues(float& Health, float& M_Health);
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
	void GetStaminaValues(float& Stamina, float& MaxStamina);
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
	void GetMentalHealthValues(float& Mental, float& MaxMental);
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	void SetHealthValues(float NewHealth, float NewMaxHealth);
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	void SetStaminaValues(float NewStamina, float NewMaxStamina);
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	void SetMentalHealthValues(float NewMentalH, float NewMaxMentalH);

	void OnHealthChangedNative(const FOnAttributeChangeData& Data);
	void OnStaminaChangedNative(const FOnAttributeChangeData& Data);
	void OnMentalChangedNative(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void OnHealthChanged(float OldValue, float NewValue);
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void OnStaminaChanged(float OldValue, float NewValue);
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void OnMentalChanged(float OldValue, float NewValue);
#pragma endregion Attribute Variables/Functions
	// Add variables Here

#pragma endregion GAS System
/*---------------------------------*/#pragma region Player Properties 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	bool isRightShoulder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float TargetArmLength;
#pragma endregion Player Camera Settings
/*---------------------------------*/#pragma region Player Movement 
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	LandingState PLandingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	AnimState PAnimationState;

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
#pragma region Movement Functions
	UFUNCTION(BlueprintCallable)
	void ImpactOnLand();

	UFUNCTION(BlueprintCallable)
	void IsSprinting();

	UFUNCTION(BlueprintCallable)
	void StopSprinting();

	//UFUNCTION(BlueprintCallable)
	//void PlayerSlide();
#pragma endregion Player Movement Functions

#pragma endregion Player Movement
/*---------------------------------*/#pragma region Player Detailed Properties
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
	FVector PlayerLocation = GetActorLocation();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
	FHitResult fHasHit;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(BlueprintReadOnly, Category = "Player Montage")
	APlayerCharacter* Character;

	UPROPERTY(EditAnywhere, Category = "Player Montage")
	UAnimMontage* SlideMontage;
private:
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;


#pragma endregion
/*---------------------------------*/#pragma region Object Handles to reduce Indentation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Nodes")
	FDoOnce DoOnce;
#pragma endregion Custom Replicates of Blueprint Functions

};
