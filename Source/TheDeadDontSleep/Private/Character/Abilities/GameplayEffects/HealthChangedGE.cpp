// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GameplayEffects/HealthChangedGE.h"

UHealthChangedGE::UHealthChangedGE()
{
	
}

void UHealthChangedGE::OnActiveGameplayEffectAddedCallback(UCharacterSystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
}

void UHealthChangedGE::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved)
{
}

