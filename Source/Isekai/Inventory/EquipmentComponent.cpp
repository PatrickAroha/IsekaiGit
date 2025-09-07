#include "EquipmentComponent.h"
#include "Isekai/Inventory/PDA_Master.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ItemSlots.SetNum(EquipmentSize);
	for (int32 i = 0; i < EquipmentSize; i++)
	{
		ItemSlots[i].Item = nullptr;
		ItemSlots[i].Quantity = 0;
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UEquipmentComponent::EquipItem(FItemSlot& ItemSlot, int32 SlotIndex)
{
	if (!IsValid(ItemSlot.Item) || !ItemSlots.IsValidIndex(SlotIndex))
		return false;

	ItemSlots[SlotIndex].Item = ItemSlot.Item;
	ItemSlots[SlotIndex].Quantity = FMath::Max(1, ItemSlot.Quantity);

	UE_LOG(LogTemp, Log, TEXT("Equipped %s in slot %d"), *ItemSlot.Item->GetName(), SlotIndex);
	return true;
}

void UEquipmentComponent::UnequipItem(int32 SlotIndex)
{
	if (!ItemSlots.IsValidIndex(SlotIndex)) return;

	ItemSlots[SlotIndex].Item = nullptr;
	ItemSlots[SlotIndex].Quantity = 0;

	UE_LOG(LogTemp, Log, TEXT("Unequipped item from slot %d"), SlotIndex);
}

bool UEquipmentComponent::HasItem(int32 SlotIndex) const
{
	if (!ItemSlots.IsValidIndex(SlotIndex)) return false;
	return ItemSlots[SlotIndex].Item != nullptr;
}

FItemSlot UEquipmentComponent::GetItemAt(int32 SlotIndex) const
{
	if (!ItemSlots.IsValidIndex(SlotIndex))
		return FItemSlot();

	return ItemSlots[SlotIndex];
}

int32 UEquipmentComponent::UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	
	int32 ParentResult = Super::UpdateSlotLeftClick(GetItemSlot, NewIndex, InventoryComponent);

	EquipItem(GetItemSlot, NewIndex);
	
	return ParentResult;
}

int32 UEquipmentComponent::UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	

	int32 ParentResult = Super::UpdateSlotRightClick(GetItemSlot, NewIndex, InventoryComponent);
	
	return ParentResult;
}

