// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Master.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    None      UMETA(DisplayName = "none"),
    Common    UMETA(DisplayName = "Common"),
    Rare      UMETA(DisplayName = "Rare"),
    Epic      UMETA(DisplayName = "Epic"),
    Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    Armor      UMETA(DisplayName = "Armor"),
    Weapon     UMETA(DisplayName = "Weapon"),
    Consumable UMETA(DisplayName = "Consumable"),
    Material   UMETA(DisplayName = "Material"),
    QuestItem  UMETA(DisplayName = "QuestItem"),
    Tool       UMETA(DisplayName = "Tool"),
    Misc       UMETA(DisplayName = "Diversos")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None  UMETA(DisplayName = "none"),
    Sword UMETA(DisplayName = "Sword"),
    Bow   UMETA(DisplayName = "Bow"),
    Staff UMETA(DisplayName = "Cajado"),
    Axe   UMETA(DisplayName = "Axe")
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
UCLASS()
class ISEKAI_API UPDA_Master : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

    static const FPrimaryAssetType PrimaryType;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(PrimaryType, GetFName());
    }
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    int32 ID = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    FText Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    int32 SpawnQuantity = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    EItemCategory Type = EItemCategory::Misc;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    EItemRarity Rarity = EItemRarity::Common;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item|Weapon", meta=(EditCondition="Type==EItemCategory::Weapon"))
    EWeaponType WeaponType = EWeaponType::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item|Consumable", meta=(EditCondition="Type==EItemCategory::Consumable"))
    EPotionType PotionType = EPotionType::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stack")
    bool bStackable = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stack", meta=(ClampMin="1", EditCondition="bStackable"))
    int32 MaxStack = 5;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visual")
    UStaticMesh* WorldMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visual")
    TObjectPtr<UTexture2D> Icon;
};
