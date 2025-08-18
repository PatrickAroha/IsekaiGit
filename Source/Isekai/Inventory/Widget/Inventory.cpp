#include "Inventory.h"

#include "ScreenPass.h"
#include "SlotInventory.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"

class USlotInventory;

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UInventory::GenerateInventory()
{
	for (int32 i = 0; i < 6; i++)
	{
		if (USlotInventory* NewSlot = CreateWidget<USlotInventory>(GetWorld(), USlotInventory::StaticClass()))
		{

			Slots.Add(NewSlot);

			NewSlot->Index = i;

			if (UGridSlot* GridSlot = Inventory->AddChildToGrid(NewSlot))
			{

				const int32 NumColumns = 3;
				int32 Row = i / NumColumns;
				int32 Column = i % NumColumns;

				GridSlot->SetRow(Row);
				GridSlot->SetColumn(Column);
			}
		}
	}
}