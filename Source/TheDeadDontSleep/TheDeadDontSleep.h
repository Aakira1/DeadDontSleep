// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	HealthSystem UMETA(DisplayName = "Health System"),
	HealAbility UMETA(DisplayName = "Healing Ability"),
	DamageAbility UMETA(DisplayName = "Damage Ability"),
	FireAbility UMETA(DisplayName = "Fire Ability")
};