// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GDDamageExecCalc.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

// Declare the attributes to capture and define how we want to capture them from the Source and Target.
struct GDDamageStatics
{
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	GDDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Damage, Source, true);

		// Capture the Target's Armor. Don't snapshot.
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Armor, Target, false);
	}
};

static const GDDamageStatics& DamageStatics()
{
	static GDDamageStatics DStatics;
	return DStatics;
}

UGDDamageExecCalc::UGDDamageExecCalc()
{
	//RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	//RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UGDDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecuteParams, OUT FGameplayEffectCustomExecutionOutput& OutExecOutput) const
{
	return;
}

