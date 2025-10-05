#include "BaseInventoryComponent.h"
#include "ItemStructure.h"
#include "PDA_Master.h"

UBaseInventoryComponent::UBaseInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UBaseInventoryComponent::UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	if (GetItemSlot.Quantity > 0 && InventoryComponent->ItemSlots.IsValidIndex(NewIndex))
	{
		if (InventoryComponent->ItemSlots[NewIndex].Quantity > 0)
		{
			if (GetItemSlot.Item == InventoryComponent->ItemSlots[NewIndex].Item && InventoryComponent->ItemSlots[NewIndex].Item->bStackable)
			{
				const int32 Espaco = InventoryComponent->ItemSlots[NewIndex].Item->MaxStack - ItemSlots[NewIndex].Quantity;
				
				if (Espaco > 0)
				{
					const int32 Add = FMath::Min(Espaco, GetItemSlot.Quantity);
					InventoryComponent->ItemSlots[NewIndex].Quantity += Add;
					return (GetItemSlot.Quantity - Add);
				}
				return(GetItemSlot.Quantity - Espaco);
			}
			Swap(InventoryComponent->ItemSlots[NewIndex], GetItemSlot);
			return GetItemSlot.Quantity;
		}
	}
	InventoryComponent->ItemSlots[NewIndex] = GetItemSlot;
	return (GetItemSlot.Quantity - InventoryComponent->ItemSlots[NewIndex].Quantity); 
}

int32 UBaseInventoryComponent::UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	if (GetItemSlot.Quantity > 0 && InventoryComponent->ItemSlots.IsValidIndex(NewIndex))
	{
		if (InventoryComponent->ItemSlots[NewIndex].Quantity > 0)
		{
			if (GetItemSlot.Item == InventoryComponent->ItemSlots[NewIndex].Item && InventoryComponent->ItemSlots[NewIndex].Item->bStackable)
			{
				const int32 Espaco = InventoryComponent->ItemSlots[NewIndex].Item->MaxStack - ItemSlots[NewIndex].Quantity;
				if (Espaco > 0)
				{
					InventoryComponent->ItemSlots[NewIndex].Quantity += 1;
					return (GetItemSlot.Quantity - 1);
				}
				return GetItemSlot.Quantity;
			}

			return GetItemSlot.Quantity;
		}
	}
	InventoryComponent->ItemSlots[NewIndex].Item = GetItemSlot.Item;
	InventoryComponent->ItemSlots[NewIndex].Quantity = 1;
	return (GetItemSlot.Quantity - 1); 
}

void UBaseInventoryComponent::ClearSlot(int32 Index)
{
	ItemSlots[Index].Item = nullptr;
	ItemSlots[Index].Quantity = 0;
}

