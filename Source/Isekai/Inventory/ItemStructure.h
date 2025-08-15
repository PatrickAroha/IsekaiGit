#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

UENUM()
enum class EItemRarity : uint8
{
    None    UMETA(DisplayName = "none"),
    Common UMETA(DisplayName = "Common"),
    Rare UMETA(DisplayName = "Rare"),
    Epic UMETA(DisplayName = "Epic"),
    Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    Armor       UMETA(DisplayName = "Armor"),
    Weapon      UMETA(DisplayName = "Weapon"),
    Consumable  UMETA(DisplayName = "Consumable"),
    Material    UMETA(DisplayName = "Material"),
    QuestItem   UMETA(DisplayName = "QuestItem"),
    Tool        UMETA(DisplayName = "Tool"),
    Misc        UMETA(DisplayName = "Diversos")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None    UMETA(DisplayName = "none"),
    Sword   UMETA(DisplayName = "Sword"),
    Bow     UMETA(DisplayName = "Bow"),
    Staff   UMETA(DisplayName = "Cajado"),
    Axe     UMETA(DisplayName = "Axe")
};

UENUM(BlueprintType)
enum class EPotionType : uint8
{
    None               UMETA(DisplayName = "none"),
    PotionHealthSmall  UMETA(DisplayName = "PotionHealthSmall"),
    PotionHealthBig    UMETA(DisplayName = "PotionHealthBig"),
    PotionManaSmall    UMETA(DisplayName = "PotionManaSmall"),
    PotionManaBig      UMETA(DisplayName = "PotionManaBig"),
    PotionStaminaSmall UMETA(DisplayName = "PotionStaminaSmall"),
    PotionStaminaBig   UMETA(DisplayName = "PotionStaminaBig")
};

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    int32 ID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    int32 SpawnQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    EItemCategory Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    EItemRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Arma")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumível")
    EPotionType PotionType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    bool bStackable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    int32 MaxStack;
    
};

USTRUCT(BlueprintType)
struct FItemSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    FItem Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    int32 Quantity;
};
