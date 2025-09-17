// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/Widget/Inv.h"  


void APlayerHUD::ToggleInventory(UInventoryComponent* InventoryComp, UEquipmentComponent* EquipmentComp)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !InventoryClass) return;
		InventoryWidget = CreateWidget<UInv>(PC, InventoryClass);
		InventoryWidget->InventoryComponent = InventoryComp;
		InventoryWidget->EquipmentComponent = EquipmentComp;
		InventoryWidget->AddToViewport();

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
		PC->FlushPressedKeys();
		PC->bShowMouseCursor = true;
}
