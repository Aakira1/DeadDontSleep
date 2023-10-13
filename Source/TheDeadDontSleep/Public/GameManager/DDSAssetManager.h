// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/AssetManager.h"
#include "DDSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class THEDEADDONTSLEEP_API UDDSAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	virtual void StartInitialLoading() override;

	
};
