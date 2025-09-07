#include "Inv.h"
#include "BaseInventory.h"
#include "Equipment.h"
#include "Components/CanvasPanel.h"

void UInv::NativeConstruct()
{
	Super::NativeConstruct();

	if (W_BaseInventory && InventoryComponent)
	{
		W_BaseInventory->InventoryComponent = InventoryComponent;
		W_BaseInventory->GenerateInventory();
		W_BaseInventory->InitItems(InventoryComponent->ItemSlots);
	}

	if (W_Equipment && EquipmentComponent)
	{
		W_Equipment->EquipmentComponent = EquipmentComponent;
		W_Equipment->GenerateInventory();
		W_Equipment->InitItems(EquipmentComponent->ItemSlots);
	}
}
