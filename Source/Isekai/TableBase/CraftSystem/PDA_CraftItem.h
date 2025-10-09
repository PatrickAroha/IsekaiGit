#pragma once

#include "Isekai/Character/IsekaiCharacter.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "PDA_CraftItem.generated.h"

UENUM(BlueprintType)
enum class ECraftingStation : uint8
{
    Forge      UMETA(DisplayName = "Forge"),
    CraftTable UMETA(DisplayName = "Craft Table"),
    Alchemy    UMETA(DisplayName = "Alchemy Table"),
};

class ABaseTableCraft;

UCLASS()
class ISEKAI_API UPDA_CraftItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FItemSlot> CraftRequeriments;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItemSlot CraftResult;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingStation CraftTableType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemCategory ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Craft")
    FName Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Craft")
    int32 Quantity;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Craft")
    UTexture2D* ItemIcon;
};
