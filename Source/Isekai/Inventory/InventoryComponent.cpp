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
	
	Quantity = AddUnique(ItemInfo, Quantity);

	return Quantity;
}

int32 UInventoryComponent::AddUnique(UPDA_Master* ItemInfo, int32 Quantity)
{
	for (int32 i = 0 ; i < InventorySize; i++)
	{
		if (Quantity <= 0) return 0;
		
		if (ItemSlots[i].Item == nullptr && ItemSlots[i].Quantity <= 0)
		{
			ItemSlots[i].Item = ItemInfo;
			ItemSlots[i].Quantity = 1;
			Quantity -= 1;
		}
	}
	return Quantity;
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

bool UInventoryComponent::HasRequiredItems(const TArray<FItemSlot>& RequiredItems)
{
	if (ItemSlots.IsEmpty()) 
		return false;

	for (const FItemSlot& Required : RequiredItems)
	{
		int32 TotalQuantity = 0;

		for (const FItemSlot& Slot : ItemSlots)
		{
			if (Slot.Item && Slot.Item->ID == Required.Item->ID)
			{
				TotalQuantity += Slot.Quantity;
			}
		}

		if (TotalQuantity < Required.Quantity)
		{
			return false;
		}
	}

	return true;
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
	Super::BeginPlay();
	
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

void UInventoryComponent::MakeNewItem(TArray<FItemSlot> RequiredItems, FItemSlot NewItem)
{
	if (HasEmptySlot())
	{
		for (FItemSlot& Slot : RequiredItems)
		{
			RemoveItem(Slot);
		}
		AddStack(NewItem.Item, NewItem.Quantity);
	}
}

bool UInventoryComponent::HasEmptySlot()
{
	for (FItemSlot& Slots : ItemSlots)
	{
		if (Slots.Item == nullptr)
		{
			return true;
		}
	}

	return false;
}

void UInventoryComponent::RemoveItem(FItemSlot Item)
{
	int32 RemoveQuantity = Item.Quantity;

	for (FItemSlot& Slot : ItemSlots)
	{
		if (Slot.Item && Slot.Item->ID == Item.Item->ID)
		{
			if (RemoveQuantity <= 0) return;
			
			if (Slot.Item && Slot.Quantity >= RemoveQuantity)
			{
				Slot.Quantity -= RemoveQuantity;
				if (Slot.Quantity == 0) Slot.Item = nullptr;
				return;
			}
			
			RemoveQuantity -= Slot.Quantity;
			Slot.Item = nullptr;
			Slot.Quantity = 0;
		}
	}
}