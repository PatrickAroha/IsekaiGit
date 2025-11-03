#pragma once

#include "CoreMinimal.h"
#include "Isekai/DialogueSystem/BaseDialogueWidgetFunction.h"
#include "Market.generated.h"

class UBaseInventory;
class UInventoryComponent;

UCLASS()
class ISEKAI_API UMarket : public UBaseDialogueWidgetFunction
{
	GENERATED_BODY()
	void NativeConstruct();

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UBaseInventory* W_BaseInventory;
};
