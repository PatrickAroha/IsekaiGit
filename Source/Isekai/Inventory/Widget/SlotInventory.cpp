#include "SlotInventory.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Isekai/Inventory/PDA_Master.h"


void USlotInventory::UpdateSlot()
{
	if (UBaseInventoryComponent* InventoryComponent = Cast<UBaseInventoryComponent>(OwnerInventory))

		if (InventoryComponent->ItemSlots.IsValidIndex(SlotIndex) && InventoryComponent->ItemSlots[SlotIndex].Item && InventoryComponent->ItemSlots[SlotIndex].Quantity > 0)
		{
			UTexture2D* IconTexture = InventoryComponent->ItemSlots[SlotIndex].Item->Icon;

			if (InventoryComponent->ItemSlots[SlotIndex].Item->Icon)
			{
				ItemIconTexture = InventoryComponent->ItemSlots[SlotIndex].Item->Icon;
				ItemIcon->SetBrushFromTexture(IconTexture);
				Quantity = InventoryComponent->ItemSlots[SlotIndex].Quantity;
				SlotIndexText->SetText(FText::AsNumber(Quantity));
				ItemInfo = InventoryComponent->ItemSlots[SlotIndex].Item;
				UE_LOG(LogTemp, Warning, TEXT("Update Slot Not Clear"));
			}
		}
		else
		{
			ItemIconTexture = nullptr;
			ItemIcon->SetBrushFromTexture(nullptr);
			SlotIndexText->SetText(FText::GetEmpty());
			Quantity = 0;
			ItemInfo = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Update Slot Clear"));
		}
}
