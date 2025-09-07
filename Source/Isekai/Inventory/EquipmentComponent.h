#pragma once

#include "CoreMinimal.h"
#include "Isekai/Inventory/BaseInventoryComponent.h"
#include "ItemStructure.h"
#include "EquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UEquipmentComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:

	UEquipmentComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment")
	int32 EquipmentSize = 4;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void EquipItem(FItemSlot& ItemSlot, int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipItem(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool HasItem(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	FItemSlot GetItemAt(int32 SlotIndex) const;

	virtual int32 UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent) override;

	virtual int32 UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent) override;

	virtual void ClearSlot(int32 Index) override;
	
};