// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "InterfaceTestActor.generated.h"

UCLASS()
class THEDEADDONTSLEEP_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInterfaceTestActor();

protected:
    
    UPROPERTY(EditAnywhere, Category="Test Actor")
    UStaticMeshComponent* Mesh;
    
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    
    virtual void BeginFocus() override;
    virtual void EndFocus() override;
    virtual void BeginInteract() override;
    virtual void EndInteract() override;
    virtual void Interact() override;
};
