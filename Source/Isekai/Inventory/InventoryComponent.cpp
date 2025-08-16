// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "PDA_Master.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int UInventoryComponent::AddItem(UPDA_Master* ItemInfo, int32 Quantity)
{
	if (ItemInfo->bStackable)
		return AddStack(ItemInfo, Quantity);

	if (ItemSlots.Num() < InventorySize)
	{
		AddUnique(ItemInfo, 1);
		return 0;
	}
	return Quantity;
}

void UInventoryComponent::AddUnique(UPDA_Master* ItemInfo, int32 Quantity)
{
	FItemSlot NewSlot;
	NewSlot.Item = ItemInfo;
	NewSlot.Quantity = Quantity;
	ItemSlots.Add(NewSlot);
}

int UInventoryComponent::AddStack(UPDA_Master* ItemInfo, int32 Quantity) 
{
	for (FItemSlot& Slots : ItemSlots)
	{
		if (Slots.Item->ID == ItemInfo->ID)
		{
			const int32 Espaco = ItemInfo->MaxStack - Slots.Quantity;
			if (Espaco > 0)
			{
				const int32 Add = FMath::Min(Espaco, Quantity);
				Slots.Quantity += Add;
				Quantity -= Add;

				if (Quantity <= 0 && ItemSlots.Num() <= InventorySize) return 0;
			}
		}
	}

	if (Quantity > 0 && ItemSlots.Num() < InventorySize)
			return NewStack(ItemInfo, Quantity);
	
	return Quantity;
	
}

int UInventoryComponent::NewStack(UPDA_Master* ItemData, int32 Quantity)
{

	while (Quantity > 0 && ItemSlots.Num() < InventorySize)
	{
		{
			const int32 Add = FMath::Min(Quantity, ItemData->MaxStack);
			FItemSlot NewSlot;
			NewSlot.Item = ItemData;
			NewSlot.Quantity = Add;
			ItemSlots.Add(NewSlot);
			Quantity -= Add;
		}
	}
	
	if (ItemSlots.Num() >= InventorySize)
			return Quantity;
		
	if (Quantity <= 0 && ItemSlots.Num() <= InventorySize)
		return 0;
	
	return Quantity;
}

void UInventoryComponent::DropItem(UPDA_Master* ItemData, int32 Quantity)
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
	ItemSlots.Empty();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

