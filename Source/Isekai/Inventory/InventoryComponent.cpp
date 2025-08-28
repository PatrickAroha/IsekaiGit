#include "InventoryComponent.h"
#include "PDA_Master.h"
#include "VisualizeTexture.h"
#include "Isekai/Character/IsekaiCharacter.h"
#include "Isekai/FunctionLibrary/DragToggle.h"
#include "Itens/BaseItem.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int UInventoryComponent::AddItem(UPDA_Master* ItemInfo, int32 Quantity)
{
	if (ItemInfo->bStackable)
		return AddStack(ItemInfo, Quantity);

	for (int32 i = 0; i < InventorySize; i++)
	{
		if (ItemSlots[i].Item == nullptr)
		{
			AddUnique(ItemInfo, 1);
			return 0;
		}
	}
	return Quantity;
}

void UInventoryComponent::AddUnique(UPDA_Master* ItemInfo, int32 Quantity)
{
	for (FItemSlot& Slots : ItemSlots)
	{
		if (Slots.Item == nullptr)
		{
			Slots.Item = ItemInfo;
			Slots.Quantity = Quantity;
			return;
		}
	}
}

int UInventoryComponent::AddStack(UPDA_Master* ItemInfo, int32 Quantity) 
{
	for (FItemSlot& Slots : ItemSlots)
	{
		if (Slots.Item != nullptr && Slots.Item->ID == ItemInfo->ID)
		{
			const int32 Espaco = ItemInfo->MaxStack - Slots.Quantity;
			if (Espaco > 0)
			{
				const int32 Add = FMath::Min(Espaco, Quantity);
				Slots.Quantity += Add;
				Quantity -= Add;

				if (Quantity <= 0) return 0;
			}
		}
	}

	for (int32 i = 0; i < InventorySize; i++)
	{
		if (Quantity > 0 && ItemSlots[i].Item == nullptr)
			return NewStack(ItemInfo, Quantity);
	}
	
	return Quantity;
	
}

int UInventoryComponent::NewStack(UPDA_Master* ItemData, int32 Quantity)
{
	for (FItemSlot& Slot : ItemSlots)
	{
		if (Slot.Item == nullptr && Quantity > 0)
		{
			const int32 Add = FMath::Min(Quantity, ItemData->MaxStack);
			Slot.Item = ItemData;
			Slot.Quantity = Add;
			Quantity -= Add;

			if (Quantity <= 0) return 0;
		}
	}
	return Quantity;
}

void UInventoryComponent::DropItem(int32 Index, int32 Quantity)
{
	if (ItemSlots.IsValidIndex(Index))
	{
		
		FItemSlot& Slot = ItemSlots[Index];

		if (Slot.Item)
		{
			AActor* Owner = GetOwner();
			if (Owner && Owner->GetWorld() && Slot.Item)
			{

				FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.f;
				FTransform SpawnTransform(Owner->GetActorRotation(), SpawnLocation);
				
				ABaseItem* Spawned = Owner->GetWorld()->SpawnActorDeferred<ABaseItem>(ABaseItem::StaticClass(), SpawnTransform);

				if (Spawned)
				{
					Spawned->ItemInfo = Slot.Item;
					Spawned->Quantity = Quantity;
					UGameplayStatics::FinishSpawningActor(Spawned, SpawnTransform);
				}
			}
		}
		if (Slot.Quantity - Quantity <= 0)
		{
			ItemSlots[Index].Item = nullptr;
			ItemSlots[Index].Quantity = 0;
		}
		else
			Slot.Quantity -= Quantity;
	}
}

void UInventoryComponent::SearchItem(UPDA_Master* ItemInfo)
{
	for (FItemSlot& Slots : ItemSlots)
	{
		if (Slots.Item->ID == ItemInfo->ID)
		{
			
		}
	}
	
}

void UInventoryComponent::UpdateSlot(FItemSlot GetItemSlot, int32 NewIndex)
{
	if (GetItemSlot.Quantity > 0 && ItemSlots.IsValidIndex(NewIndex))
	{
		ItemSlots[NewIndex] = GetItemSlot;

	}
}

void UInventoryComponent::ClearSlot(int32 Index)
{
	ItemSlots[Index].Item = nullptr;
	ItemSlots[Index].Quantity = 0;
}

void UInventoryComponent::ClearInventory()
{
	for (int32 i = 0 ; i < InventorySize; i++)
	{
		ItemSlots[i].Item = nullptr;
		ItemSlots[i].Quantity = 0;
	}
	
}

void UInventoryComponent::BeginPlay()
{
	ItemSlots.SetNum(InventorySize);
	for (int32 i = 0; i < InventorySize; i++)
	{
		ItemSlots[i].Item = nullptr;
		ItemSlots[i].Quantity = 0;
	}
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

