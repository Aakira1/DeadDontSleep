// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/Items/ItemBase.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::CreateItemCopy() const
{
    UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

    ItemCopy->ID = this->ID;
    ItemCopy->Quantity = this->Quantity;
    ItemCopy->ItemQuality = this->ItemQuality;
    ItemCopy->ItemType = ItemCopy->ItemType;
    ItemCopy->TextData = this->TextData;
    ItemCopy->NumericData = this->NumericData;
    ItemCopy->ItemStatistics = this->ItemStatistics;
    ItemCopy->AssetData = this->AssetData;
    ItemCopy->ItemTag = this->ItemTag;
    ItemCopy->ItemTagContainer = this->ItemTagContainer;

    return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
    if (NewQuantity != Quantity)
    {
        Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ?  NumericData.MaxStackSize : 1);

       //if (OwningInventory)
       //{
       // if(Quantity < 0)
       //{
       //  owningInventory->RemoveItem(this);  
       //}
       //}
    }

    
}

void UItemBase::Use(APlayerCharacter* Character)
{
}


