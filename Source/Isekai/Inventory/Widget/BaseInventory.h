#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/ItemStructure.h"
#include "BaseInventory.generated.h"


struct FItemSlot;
class USlotInventory;
class UGridPanel;
class UButton;

UCLASS(Blueprintable, BlueprintType)
class ISEKAI_API UBaseInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* CloseWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* InventoryGrid = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI | Inventory")
	TArray<TObjectPtr<USlotInventory>> Slots;

	UPROPERTY(EditAnywhere, Category = "UI | Inventory")
	TSubclassOf<UUserWidget> SlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TArray<FItemSlot> ItemSlots;
	
	UFUNCTION(BlueprintCallable)
	void InitItems(const TArray<FItemSlot>& ItemSlotsCopy);

	
protected:
	virtual bool Initialize() override;

	void FillSlots();
	
public:
	void GenerateInventory();
};