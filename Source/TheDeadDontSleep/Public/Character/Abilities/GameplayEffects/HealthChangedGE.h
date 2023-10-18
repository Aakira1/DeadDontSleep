// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterSystemComponent.h"
#include "GameplayEffect.h"
#include "HealthChangedGE.generated.h"

/**
 * 
 */
UCLASS()
class THEDEADDONTSLEEP_API UHealthChangedGE : public UGameplayEffect
{
	GENERATED_BODY()

protected:
	//Objects
	UCharacterSystemComponent* ASystemComponent;

	//Variables
public:
	UHealthChangedGE();



	virtual void OnActiveGameplayEffectAddedCallback(UCharacterSystemComponent* Target, const FGameplayEffectSpec& SpecApplied,
		FActiveGameplayEffectHandle ActiveHandle);
	virtual void OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved);
};
