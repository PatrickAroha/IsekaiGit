#pragma once

#include "CoreMinimal.h"
#include "FurnaceInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Isekai/Inventory/Widget/BaseInventory.h"
#include "Isekai/Inventory/Widget/SlotInventory.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "FurnaceWidget.generated.h"

class UProgressBar;
class UFurnaceInventoryComponent;
class AFurnaceTable;

UCLASS()
class ISEKAI_API UFurnaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RefreshSlots();

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	UFurnaceInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	UInventoryComponent* PlayerInventoryComponent;

	UPROPERTY(meta = (BindWidget))
	UBaseInventory* W_BaseInventory;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere )
	USlotInventory* W_SlotInventory_1;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere )
	USlotInventory* W_SlotInventory_2;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere )
	USlotInventory* W_SlotInventory_3;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere )
	UProgressBar* CurrentEnergy;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere )
	UProgressBar* PercentegeOfMelt;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	AFurnaceTable* OwnerTable;

	UFUNCTION() void UpdateFuelSlot() { InventoryComponent->UpdateItem(0); }
	UFUNCTION() void UpdateSmeltSlot() { InventoryComponent->UpdateItem(1); }
	UFUNCTION() void UpdateResultSlot() { InventoryComponent->UpdateItem(2); }
};
