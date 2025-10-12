#include "FurnaceWidget.h"
#include "FurnaceInventoryComponent.h"
#include "Components/ProgressBar.h"

void UFurnaceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!InventoryComponent || !CurrentEnergy || !PercentegeOfMelt)
		return;

	if (InventoryComponent->MaxEnergy > 0 )
	CurrentEnergy->SetPercent(InventoryComponent->CurrentEnergy / InventoryComponent->MaxEnergy);
	PercentegeOfMelt->SetPercent(InventoryComponent->PercentageOfMelt / InventoryComponent->SmeltDuration);
}

void UFurnaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!InventoryComponent || !PlayerInventoryComponent) return;

	
	if (W_SlotInventory_1 && InventoryComponent->ItemSlots.IsValidIndex(0))
	{
		W_SlotInventory_1->OwnerInventory = InventoryComponent;
		W_SlotInventory_1->SlotIndex = 0;
		W_SlotInventory_1->OnSlotUpdated.AddDynamic(this, &UFurnaceWidget::UpdateFuelSlot);
	}

	if (W_SlotInventory_2 && InventoryComponent->ItemSlots.IsValidIndex(1))
	{
		W_SlotInventory_2->OwnerInventory = InventoryComponent;
		W_SlotInventory_2->SlotIndex = 1;
		W_SlotInventory_2->OnSlotUpdated.AddDynamic(this, &UFurnaceWidget::UpdateSmeltSlot);
	}

	if (W_SlotInventory_3 && InventoryComponent->ItemSlots.IsValidIndex(2))
	{
		W_SlotInventory_3->OwnerInventory = InventoryComponent;
		W_SlotInventory_3->SlotIndex = 2;
		W_SlotInventory_3->OnSlotUpdated.AddDynamic(this, &UFurnaceWidget::UpdateResultSlot);
	}

	RefreshSlots();
	
	if (W_BaseInventory)
	{
		W_BaseInventory->InventoryComponent = PlayerInventoryComponent;
		W_BaseInventory->GenerateInventory();
		W_BaseInventory->InitItems(PlayerInventoryComponent->ItemSlots);
	}
	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
		PC->FlushPressedKeys();
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
	}

	InventoryComponent->OnItemUpdated.AddDynamic(this, &UFurnaceWidget::RefreshSlots);

	
}

void UFurnaceWidget::RefreshSlots()
{
	if (!InventoryComponent) return;

	const TArray<FItemSlot>& Slots = InventoryComponent->ItemSlots;

	auto UpdateVisual = [](USlotInventory* SlotWidget, const FItemSlot& ItemSlot)
	{
		if (!SlotWidget) return;

		if (ItemSlot.Item && ItemSlot.Quantity > 0)
		{
			SlotWidget->ItemInfo = ItemSlot.Item;
			SlotWidget->Quantity = ItemSlot.Quantity;
			SlotWidget->ItemIconTexture = ItemSlot.Item->Icon;

			if (SlotWidget->ItemIcon)
				SlotWidget->ItemIcon->SetBrushFromTexture(ItemSlot.Item->Icon);
			if (SlotWidget->SlotIndexText)
				SlotWidget->SlotIndexText->SetText(FText::AsNumber(ItemSlot.Quantity));
		}
		else
		{
			SlotWidget->ItemInfo = nullptr;
			SlotWidget->Quantity = 0;
			SlotWidget->ItemIconTexture = nullptr;

			if (SlotWidget->ItemIcon)
				SlotWidget->ItemIcon->SetBrushFromTexture(nullptr);
			if (SlotWidget->SlotIndexText)
				SlotWidget->SlotIndexText->SetText(FText::GetEmpty());
		}
	};
	
	if (Slots.IsValidIndex(0)) UpdateVisual(W_SlotInventory_1, Slots[0]);
	if (Slots.IsValidIndex(1)) UpdateVisual(W_SlotInventory_2, Slots[1]);
	if (Slots.IsValidIndex(2)) UpdateVisual(W_SlotInventory_3, Slots[2]);
}

