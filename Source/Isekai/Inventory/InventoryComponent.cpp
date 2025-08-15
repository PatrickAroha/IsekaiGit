// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent(): ItemDataTable(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

int UInventoryComponent::AddItem(FItem ItemData, int32 Quantity)
{
	if (ItemData.bStackable)
		return AddStack(ItemData, Quantity);

	if (ItemSlot.Num() < InventorySize)
	{
		AddUnique(ItemData, 1);
		return 0;
	}
	return Quantity;
}

void UInventoryComponent::AddUnique(FItem ItemData, int32 Quantity)
{
	FItemSlot NewSlot;
	NewSlot.Item = ItemData;
	NewSlot.Quantity = Quantity;
	ItemSlot.Add(NewSlot);
}

int UInventoryComponent::AddStack(FItem ItemData, int32 Quantity) 
{
	for (FItemSlot& Slots : ItemSlot)
	{
		if (Slots.Item.ID == ItemData.ID)
		{
			const int32 Espaco = ItemData.MaxStack - Slots.Quantity;
			if (Espaco > 0)
			{
				const int32 Add = FMath::Min(Espaco, Quantity);
				Slots.Quantity += Add;
				Quantity -= Add;

				if (Quantity <= 0 && ItemSlot.Num() <= InventorySize) return 0;
			}
		}
	}

	if (Quantity > 0 && ItemSlot.Num() < InventorySize)
			return NewStack(ItemData, Quantity);
	
	return Quantity;
	
}

int UInventoryComponent::NewStack(FItem ItemData, int32 Quantity)
{

	while (Quantity > 0 && ItemSlot.Num() < InventorySize)
	{
		{
			const int32 Add = FMath::Min(Quantity, ItemData.MaxStack);
			FItemSlot NewSlot;
			NewSlot.Item = ItemData;
			NewSlot.Quantity = Add;
			ItemSlot.Add(NewSlot);
			Quantity -= Add;
		}
	}
	
	if (ItemSlot.Num() >= InventorySize)
			return Quantity;
		
	if (Quantity <= 0 && ItemSlot.Num() <= InventorySize)
		return 0;
	
	return Quantity;
}

void UInventoryComponent::DropItem(FItem ItemData, int32 Quantity)
{
	
}

void UInventoryComponent::RemoveItem()
{
	
}

void UInventoryComponent::SearchItem()
{
	
}

void UInventoryComponent::ClearInventory()
{
	ItemSlot.Empty();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

