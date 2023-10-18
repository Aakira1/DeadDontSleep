// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Character/Abilities/CharacterSystemComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "CharacterAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h (Boilerplate MACRO)
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class THEDEADDONTSLEEP_API UCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UCharacterAttributeSetBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Stamina)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxStamina)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mindset") 
	FGameplayAttributeData MentalHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MentalHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mindset")
	FGameplayAttributeData MaxMentalHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxMentalHealth)

		/* Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into
		   Temporary Value - Not Replicated
		*/
		UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Damage)
};
