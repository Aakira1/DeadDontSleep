// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameManager/Data/ItemDataStruct.h>

#include "Character/Player/PlayerCharacter.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class THEDEADDONTSLEEP_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
    // ===============================================================================
    // Properties & Variables
    // ===============================================================================
    //UPROPERTY()
    //UInventoryComponent* OwningInventory;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FName ID;
    
    UPROPERTY(VisibleAnywhere, Category="Item")
    int32 Quantity{0};

    UPROPERTY(VisibleAnywhere, Category = "Item")
    EItemType ItemType;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    EItemQuality ItemQuality;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemStatistics ItemStatistics;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemTextData TextData;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemNumericData NumericData;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemAssetData AssetData;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FGameplayTag ItemTag;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FGameplayTagContainer ItemTagContainer;
    
    // ===============================================================================
    // Functions
    // ===============================================================================
    UItemBase();

    UItemBase* CreateItemCopy() const;

    UFUNCTION(Category =  "Item")
    FORCEINLINE float GetItemStackWeight() const {return Quantity * NumericData.weight;};
    UFUNCTION(Category =  "Item")
    FORCEINLINE float GetItemSingleWeight() const {return NumericData.weight;};
    UFUNCTION(Category =  "Item")
    FORCEINLINE bool IsFullItemStack() const {return Quantity == NumericData.MaxStackSize;};

    void SetQuantity(const int32 NewQuantity);

    virtual void Use(APlayerCharacter* Character);

protected:
    // ===============================================================================
    // Properties & Variables
    // ===============================================================================
    bool operator==(const FName& OtherID) const
    {
      return this->ID == OtherID;  
    };

    bool operator==(const FGameplayTag& OtherTag) const
    {
      return this->ItemTag == OtherTag;  
    };

    bool operator==(const FGameplayTagContainer& OtherTagContainer) const
    {
        return this->ItemTagContainer == OtherTagContainer;  
    };
    
    // ===============================================================================
    // Functions
    // ===============================================================================
};
