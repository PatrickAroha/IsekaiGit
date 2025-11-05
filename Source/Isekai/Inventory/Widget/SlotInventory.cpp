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
				ItemIcon->SetVisibility(ESlateVisibility::Visible);
				ItemIcon->SetBrushFromTexture(IconTexture);
				Quantity = InventoryComponent->ItemSlots[SlotIndex].Quantity;
				BGText->SetVisibility(ESlateVisibility::Visible);
				SlotIndexText->SetText(FText::AsNumber(Quantity));
				ItemInfo = InventoryComponent->ItemSlots[SlotIndex].Item;
			}
		}
		else
		{
			ItemIconTexture = nullptr;
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			BGText->SetVisibility(ESlateVisibility::Hidden);
			Quantity = 0;
			ItemInfo = nullptr;
		}

	OnSlotUpdated.Broadcast();
	
}

