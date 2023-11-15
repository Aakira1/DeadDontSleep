#pragma once

#include "Engine.h"
#include "GameplayTagContainer.h"
#include "ItemDataStruct.generated.h"



UENUM()
enum class EItemQuality : uint8
{
    Aged UMETA(DisplayName = "Aged"),
    Common UMETA(DisplayName = "Common"),
    Uncommon UMETA(DisplayName = "Un-Common"),
    Quality UMETA(DisplayName = "Quality"),
    Master UMETA(DisplayName = "Master"),
    Warlock UMETA(DisplayName = "Warlock")
};

UENUM()
enum class EItemType : uint8
{
    Armor UMETA(DisplayName = "Armor"),
    Weapon UMETA(DisplayName = "Weapon"),
    Shield UMETA(DisplayName = "Shield"),
    Consumable UMETA(DisplayName = "Consumable"),
    Quest UMETA(DisplayName = "Quest"),
    Mundane UMETA(DisplayName = "Mundane")
};

USTRUCT()
struct FItemStatistics
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    float ArmorRating;

    UPROPERTY(EditAnywhere)
    float HealingAmount;

    UPROPERTY(EditAnywhere)
    float HungerAmount;

    UPROPERTY(EditAnywhere)
    float MedicineAmount;

    UPROPERTY(EditAnywhere)
    float DamageAmount;

    UPROPERTY(EditAnywhere)
    bool bHoldsLiquid;

    UPROPERTY(EditAnywhere)
    float LiquidVolume;

    UPROPERTY(EditAnywhere)
    float SellValue;
};

USTRUCT()
struct FItemTextData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    FText Name;

    UPROPERTY(EditAnywhere)
    FText Description;

    UPROPERTY(EditAnywhere)
    FText InteractionText;

    UPROPERTY(EditAnywhere)
    FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    float weight;

    UPROPERTY(EditAnywhere)
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere)
    bool bIsStackable;

    UPROPERTY(EditAnywhere)
    bool bIsNPCInventory;

    UPROPERTY(EditAnywhere)
    bool bIsInventoryStorage;

    UPROPERTY(EditAnywhere)
    bool bIsInventoryEquipped;

    UPROPERTY(EditAnywhere)
    bool bIsInventoryType;

    UPROPERTY(EditAnywhere)
    bool bIsItemAttachable;
};

USTRUCT()
struct FItemAssetData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere)
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere)
    USoundCue* ItemStore;

    UPROPERTY(EditAnywhere)
    USoundCue* ItemAttached;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FName ID;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    EItemQuality ItemQuality;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FItemStatistics ItemStatistics;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FItemTextData TextData;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FItemNumericData NumericData;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FItemAssetData AssetData;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FGameplayTag ItemTag;

    UPROPERTY(EditAnywhere, Category = "Item Data")
    FGameplayTagContainer ItemTagContainer;

};