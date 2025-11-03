#include "Market.h"
#include "Isekai/Inventory/Widget/BaseInventory.h"

void UMarket::NativeConstruct()
{
	Super::NativeConstruct();

	if (W_BaseInventory && InventoryComponent)
	
	{
		W_BaseInventory->InventoryComponent = InventoryComponent;
		W_BaseInventory->GenerateInventory();
		W_BaseInventory->InitItems(InventoryComponent->ItemSlots);

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = true;

			PC->FlushPressedKeys();
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputMode);
		}
	}
}
