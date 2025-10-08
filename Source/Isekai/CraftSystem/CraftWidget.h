#pragma once

#include "CoreMinimal.h"
#include "PDA_CraftItem.h"
#include "Blueprint/UserWidget.h"
#include "CraftWidget.generated.h"

class UScrollBox;

UCLASS()
class ISEKAI_API UCraftWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadWrite)
	UScrollBox* ItensList;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Craft")
	TArray<UPDA_CraftItem*> UnlockedsRecipes;

	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UBaseInventory* W_BaseInventory;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Craft")
	void OnRecipesReceived();
	
	void NativeConstruct();
};
