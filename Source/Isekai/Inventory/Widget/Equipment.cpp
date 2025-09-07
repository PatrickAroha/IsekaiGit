#include "Equipment.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "SlotInventory.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Blueprint/WidgetTree.h"


bool UEquipment::Initialize()
{
	Super::Initialize();
	
	return true;
}

void UEquipment::GenerateInventory()
{
	if (!InventoryGrid || !SlotClass)
	{
		return;
	}

	InventoryGrid->ClearChildren();
	Slots.Empty();

	const int32 NumberOfSlots = 4;
	const int32 NumColumns = 2;

	for (int32 i = 0; i < NumberOfSlots; i++)
	{
		if (USlotInventory* NewSlot = CreateWidget<USlotInventory>(this, SlotClass))
		{
			Slots.Add(NewSlot);
			NewSlot->SlotIndex = i;
			NewSlot->OwnerInventory = EquipmentComponent;

			// 🔹 Criar um SizeBox para forçar tamanho fixo
			USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
			SizeBox->SetWidthOverride(85.f);   // largura do slot
			SizeBox->SetHeightOverride(85.f);  // altura do slot

			// Adicionar o SlotInventory dentro do SizeBox
			SizeBox->AddChild(NewSlot);

			// Agora adicionar o SizeBox no GridPanel
			if (UGridSlot* GridSlot = InventoryGrid->AddChildToGrid(SizeBox))
			{
				const int32 Row = i / NumColumns;
				const int32 Column = i % NumColumns;

				GridSlot->SetRow(Row);
				GridSlot->SetColumn(Column);

				GridSlot->SetPadding(FMargin(17.f)); // espaçamento entre os slots
				GridSlot->SetHorizontalAlignment(HAlign_Center);
				GridSlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
}


void UEquipment::InitItems(const TArray<FItemSlot>& ItemSlotsCopy)
{
	ItemSlots = ItemSlotsCopy;
	FillSlots();
}

void UEquipment::FillSlots()
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
