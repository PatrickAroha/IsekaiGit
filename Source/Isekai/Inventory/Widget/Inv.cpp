#include "Inv.h"
#include "BaseInventory.h"
#include "Equipment.h"

void UInv::NativeConstruct()
{
	Super::NativeConstruct();

	// Corrigido: verificação da classe de inventário
	if (InventoryClass)
	{
		InventoryWidget = CreateWidget<UBaseInventory>(GetWorld(), InventoryClass);
		if (InventoryWidget && InventoryComponent)
		{
			InventoryWidget->InventoryComponent = InventoryComponent;
			InventoryWidget->GenerateInventory();
			InventoryWidget->InitItems(InventoryComponent->ItemSlots);
			InventoryWidget->AddToViewport();
		}
	}

	if (EquipmentClass)
	{
		EquipmentWidget = CreateWidget<UEquipment>(GetWorld(), EquipmentClass);
		if (EquipmentWidget && EquipmentComponent)
		{
			EquipmentWidget->EquipmentComponent = EquipmentComponent;
			EquipmentWidget->GenerateInventory();
			EquipmentWidget->InitItems(EquipmentComponent->ItemSlots);
			EquipmentWidget->AddToViewport();
		}
	}
}
