// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/CharacterSystemComponent.h"

void UCharacterSystemComponent::ReceiveDamage(UCharacterSystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}

