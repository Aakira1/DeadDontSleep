// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../TheDeadDontSleep.h"
#include "GGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class THEDEADDONTSLEEP_API UGGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAbilityInputID AbilityInputID{	EAbilityInputID::None };
};