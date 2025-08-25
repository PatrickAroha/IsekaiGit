#include "BaseInventory.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Button.h"
#include "SlotInventory.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "BaseInventory.h"
#include "SlotInventory.h"
#include "Components/Image.h"

bool UBaseInventory::Initialize()
{
	Super::Initialize();

	GenerateInventory();
	
	return true;
}

void UBaseInventory::GenerateInventory()
{
	if (!InventoryGrid || !SlotClass)
	{
		return;
	}

	InventoryGrid->ClearChildren();
	Slots.Empty();

	const int32 NumberOfSlots = 6;
	const int32 NumColumns = 3;

	for (int32 i = 0; i < NumberOfSlots; i++)
	{
		if (USlotInventory* NewSlot = CreateWidget<USlotInventory>(this, SlotClass))
		{
			Slots.Add(NewSlot);
			NewSlot->SlotIndex = i;
			NewSlot->OwnerInventory = this;
			
			if (UGridSlot* GridSlot = InventoryGrid->AddChildToGrid(NewSlot))
			{
				const int32 Row = i / NumColumns;
				const int32 Column = i % NumColumns;

				GridSlot->SetRow(Row);
				GridSlot->SetColumn(Column);
			}
		}
	}
}

void UBaseInventory::InitItems(const TArray<FItemSlot>& ItemSlotsCopy)
{
	ItemSlots = ItemSlotsCopy;
	FillSlots();
}

void UBaseInventory::FillSlots()
{
	if (Slots.Num() > 0 && Slots[0])
	{
		for (int32 i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i])
			{
				if (ItemSlots.IsValidIndex(i) && ItemSlots[i].Item && ItemSlots[i].Quantity > 0)
				{
					UTexture2D* IconTexture = ItemSlots[i].Item->Icon;

					if (IconTexture && Slots[i]->ItemIcon)
					{
						Slots[i]->ItemIconTexture = IconTexture;
						Slots[i]->ItemIcon->SetBrushFromTexture(IconTexture);
						Slots[i]->SlotIndexText->SetText(FText::AsNumber(ItemSlots[i].Quantity));
						Slots[i]->Quantity = ItemSlots[i].Quantity;
						Slots[i]->ItemInfo = ItemSlots[i].Item;
					}
				}
				else
				{
					Slots[i]->ItemIconTexture = nullptr;
					Slots[i]->ItemIcon->SetBrushFromTexture(nullptr);
					Slots[i]->SlotIndexText->SetText(FText::GetEmpty());
					Slots[i]->Quantity = 0;
					Slots[i]->ItemInfo = nullptr;
				}
			}
		}
	}
}