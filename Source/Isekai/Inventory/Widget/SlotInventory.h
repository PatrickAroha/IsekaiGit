#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SlotInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotUpdated);

class UInventoryComponent;
class UBaseInventoryComponent;
class UPDA_Master;

UCLASS()
class ISEKAI_API USlotInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSlotUpdated OnSlotUpdated;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotIndex;

	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadOnly)
	UTextBlock* SlotIndexText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemIconTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UPDA_Master* ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32 Quantity;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	UBaseInventoryComponent* OwnerInventory;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	UInventoryComponent* Inv;

	UFUNCTION(BlueprintCallable)
	void UpdateSlot();
	void HasSlotInteract();
};
