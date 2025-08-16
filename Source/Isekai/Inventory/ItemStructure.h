#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

class UPDA_Master;

USTRUCT(BlueprintType)
struct FItemSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    UPDA_Master* Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    int32 Quantity;
};
