// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWidget.h"

void UCraftWidget::NativeConstruct()
{

	Super::NativeConstruct();

	if (W_BaseInventory && InventoryComponent)
	{
		W_BaseInventory->InventoryComponent = InventoryComponent;
		W_BaseInventory->GenerateInventory();
		W_BaseInventory->InitItems(InventoryComponent->ItemSlots);
	}
}