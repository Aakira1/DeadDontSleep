// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DDSAssetManager.h"
#include "AbilitySystemGlobals.h"

void UDDSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Asset Manager Initialized"));
}
