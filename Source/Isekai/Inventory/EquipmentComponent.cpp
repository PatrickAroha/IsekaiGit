#include "EquipmentComponent.h"
#include "Isekai/AtributesSystem/AtributosSystem.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "Itens/ObjectItemBase.h"

UEquipmentComponent::UEquipmentComponent(): ItemEquiped()
{
	PrimaryComponentTick.bCanEverTick = false;

	ItemSlots.SetNum(EquipmentSize);
	AllowedTypes.SetNum(EquipmentSize);

	for (int32 i = 0; i < EquipmentSize; i++)
	{
		ItemSlots[i].Item = nullptr;
		ItemSlots[i].Quantity = 0;
	}

	AllowedTypes[0] = EItemCategory::Weapon;
	AllowedTypes[1] = EItemCategory::Armor;
	AllowedTypes[2] = EItemCategory::Consumable;
	AllowedTypes[3] = EItemCategory::Consumable;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::EquipItem(FItemSlot& ItemSlot, int32 SlotIndex)
{
	if (!IsValid(ItemSlot.Item) || !ItemSlots.IsValidIndex(SlotIndex))
		return;

	if (AActor* Owner = GetOwner())
	{
		if (UAtributosSystem* Atribs = Owner->FindComponentByClass<UAtributosSystem>())
		{
			for (const TPair<EAtributeType, float>& Bonus : ItemSlots[SlotIndex].Item->AttributeBonus)
			{
				Atribs->AddBonusValue(Bonus.Key, Bonus.Value);
			}

			if (ItemSlot.Item && ItemSlot.Item->Type == EItemCategory::Consumable)
			{
				EquipPotion(ItemSlot, SlotIndex);
			}
		}
	}
}

void UEquipmentComponent::UnequipItem(int32 SlotIndex)
{
	if (!ItemSlots.IsValidIndex(SlotIndex)) return;

	if (AActor* Owner = GetOwner())
	{
		if (UAtributosSystem* Atribs = Owner->FindComponentByClass<UAtributosSystem>())
		{
			if (ItemSlots[SlotIndex].Item && ItemSlots[SlotIndex].Item->AttributeBonus.Num() > 0)
			{
				for (const TPair<EAtributeType, float>& Bonus : ItemSlots[SlotIndex].Item->AttributeBonus)
				{
					Atribs->RemoveValue(Bonus.Key, Bonus.Value);
				}
			}

			ItemEquiped.Item = nullptr;
			ItemEquiped.Quantity = 0;
			EquipPotion(ItemEquiped, SlotIndex);
			
		}
	}
}

bool UEquipmentComponent::HasItem(int32 SlotIndex) const
{
	if (!ItemSlots.IsValidIndex(SlotIndex)) return false;
	return ItemSlots[SlotIndex].Item != nullptr;
}

FItemSlot UEquipmentComponent::GetItemAt(int32 SlotIndex) const
{
	if (!ItemSlots.IsValidIndex(SlotIndex))
		return FItemSlot();

	return ItemSlots[SlotIndex];
}

int32 UEquipmentComponent::UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	if (!IsValid(GetItemSlot.Item) || !GetItemSlot.Item->bEquipable)
		return GetItemSlot.Quantity;

	if (!AllowedTypes.IsValidIndex(NewIndex) || AllowedTypes[NewIndex] != GetItemSlot.Item->Type)
		return GetItemSlot.Quantity;

	UnequipItem(NewIndex);
	
	int32 ParentResult = Super::UpdateSlotLeftClick(GetItemSlot, NewIndex, InventoryComponent);

	if (ItemSlots.IsValidIndex(NewIndex) && ItemSlots[NewIndex].Item)
	{
		EquipItem(ItemSlots[NewIndex], NewIndex);
	}
	
	return ParentResult;
}

int32 UEquipmentComponent::UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent)
{
	if (!IsValid(GetItemSlot.Item) || !GetItemSlot.Item->bEquipable)
		return GetItemSlot.Quantity;

	if (!AllowedTypes.IsValidIndex(NewIndex) || AllowedTypes[NewIndex] != GetItemSlot.Item->Type)
		return GetItemSlot.Quantity;
	
	UnequipItem(NewIndex);

	int32 ParentResult = Super::UpdateSlotRightClick(GetItemSlot, NewIndex, InventoryComponent);

	if (ItemSlots.IsValidIndex(NewIndex) && ItemSlots[NewIndex].Item)
	{
		EquipItem(ItemSlots[NewIndex], NewIndex);
	}
	
	return ParentResult;
}

void UEquipmentComponent::ClearSlot(int32 Index)
{
	UnequipItem(Index);
	Super::ClearSlot(Index);
}

void UEquipmentComponent::NextEquipItem()
{
	if (EquipmentSize <= 0) return;

	int32 StartIndex = PotionEquipIndex;
	
	do
	{
		PotionEquipIndex++;
		if (PotionEquipIndex >= EquipmentSize)
		{
			PotionEquipIndex = 0;
		}

		const FItemSlot& Slot = ItemSlots[PotionEquipIndex];
		if (Slot.Item && Slot.Item->Type == EItemCategory::Consumable)
		{
			EquipPotion(ItemSlots[PotionEquipIndex], PotionEquipIndex);
			return;
		}

	} while (PotionEquipIndex != StartIndex);
	
	ItemEquiped = FItemSlot();
	OnPotionChanged.Broadcast(ItemEquiped);
}

void UEquipmentComponent::EquipPotion(FItemSlot& Item, int32 Index)
{

	PotionEquipIndex = Index;
	ItemEquiped = Item;
	OnPotionChanged.Broadcast(ItemEquiped);
	
}

void UEquipmentComponent::Use()
{
	FItemSlot& PotionSlot = ItemSlots[PotionEquipIndex];

	if (AIsekaiCharacter* Player = Cast<AIsekaiCharacter>(GetOwner()))
	{
		if (Player->StatusComponent)
		{
			PotionSlot.Item->ItemLogic->Use(Cast<AIsekaiCharacter>(GetOwner()));

			if (ItemSlots[PotionEquipIndex].Quantity <= 1) ClearSlot(PotionEquipIndex);

			else ItemSlots[PotionEquipIndex].Quantity--;
		}
	}
}

