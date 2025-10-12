#include "FurnaceInventoryComponent.h"
#include "Isekai/Inventory/PDA_Master.h"

void UFurnaceInventoryComponent::DropItem(int32 Index, int32 Quantity)
{

}

UFurnaceInventoryComponent::UFurnaceInventoryComponent(): FuelItemSlot(), SmeltableItemSlot()
{
	InventorySize = 3;
}


void UFurnaceInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UFurnaceInventoryComponent::UpdateItem(int32 SlotIndex)
{
	if (OnCooking)
	{
		if (!GetWorld()) return;
		if (SlotIndex == 0 && SmeltableItemSlot.Item != ItemSlots[0].Item) { ResetSmeltItem(); GetWorld()->GetTimerManager().ClearTimer(FurnaceTimerHandle); SmeltableItem(0); return; }
		if (SlotIndex == 1 && FuelItemSlot.Item != ItemSlots[1].Item) { }
	}
	
	if (ItemSlots[SlotIndex].Item)
	{
		if (ItemSlots[SlotIndex].Item->Type == EItemCategory::Material)
		{
			if (SlotIndex == 0) { SmeltableItem(SlotIndex); return; }
			
			if (SlotIndex == 1) { FuelItem(SlotIndex);}
		}
	}
}

void UFurnaceInventoryComponent::SmeltableItem(int32 SlotIndex)
{
	if (!ItemSlots[SlotIndex].Item) return;
	
	if (ItemSlots[SlotIndex].Item->bSmeltable)
	{
		bIsSmeltableItem = true;
		SmeltableDensity = ItemSlots[SlotIndex].Item->SmeltableDensity;
		SmeltableItemSlot= ItemSlots[SlotIndex];
		Melt();
		return;
	}

	PercentageOfMelt = 0;
	bIsSmeltableItem = false;
	SmeltableDensity = 0;
	SmeltableItemSlot.Item = nullptr;
	SmeltableItemSlot.Quantity = 0;
}

void UFurnaceInventoryComponent::FuelItem(int32 SlotIndex)
{
	if (!ItemSlots[SlotIndex].Item) return;
	
	if (ItemSlots[SlotIndex].Item->bFuel)
	{
		bIsFuelItem = true;
		FuelItemSlot = ItemSlots[SlotIndex];
		Melt();
		return;
	}

	bIsFuelItem = false;
	FuelPower = 0;
	FuelItemSlot.Item = nullptr;
	FuelItemSlot.Quantity = 0;
}

void UFurnaceInventoryComponent::Melt()
{
	if (!GetWorld()) return;
	if (GetWorld()->GetTimerManager().IsTimerActive(FurnaceTimerHandle)) return;
	if (!bIsFuelItem || !bIsSmeltableItem) return;

	UPDA_Master* Result = ItemSlots[0].Item ? ItemSlots[0].Item->SmeltItemResult.Item : nullptr;
	if (!Result) return;

	if (ItemSlots[2].Item &&
		ItemSlots[2].Item->GetPrimaryAssetId() != Result->GetPrimaryAssetId()) return;
		
	if (ItemSlots[0].Quantity > 0)
	{
		if (CurrentEnergy <= 0) ConsumeFuel();
		CalculateTimeOfCook();
		OnCooking = true;

		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().SetTimer(
		FurnaceTimerHandle,
		this,
		&UFurnaceInventoryComponent::Cooking,
		SmeltFrequency,
		true);
		
	}
	OnItemUpdated.Broadcast();

}

void UFurnaceInventoryComponent::CalculateTimeOfCook()
{
	float ScaleOfMeth = ( SmeltableDensity / FuelPotency );
	SmeltDuration = 10 * FMath::Max(ScaleOfMeth, 1.0f);
}

void UFurnaceInventoryComponent::ConsumeFuel()
{
	if (!ItemSlots[1].Item) return;
	
	MaxEnergy = ItemSlots[1].Item->FuelEnergy;
	CurrentEnergy = ItemSlots[1].Item->FuelEnergy;
	FuelPotency = ItemSlots[1].Item->FuelPotency;
	
	SubtractSlot(1);
}

void UFurnaceInventoryComponent::Cooking()
{
	if (PercentageOfMelt >= SmeltDuration)
	{
		FinishSmelting();
	}

	if (ItemSlots[2].Item && ItemSlots[2].Quantity == ItemSlots[2].Item->MaxStack) {if (!GetWorld()) return; GetWorld()->GetTimerManager().ClearTimer(FurnaceTimerHandle); OnCooking = false; } 
	
	if (CurrentEnergy > 0 && ItemSlots[0].Quantity > 0) { PercentageOfMelt = PercentageOfMelt + 0.1; CurrentEnergy -= SmeltFrequency; }
	else if (CurrentEnergy > 0) CurrentEnergy -= SmeltFrequency;
	else if (ItemSlots[0].Quantity > 0 && CurrentEnergy <= 0) { ConsumeFuel(); OnItemUpdated.Broadcast(); }
	else if (CurrentEnergy <= 0 && ItemSlots[0].Quantity <= 0) {if (!GetWorld()) return; GetWorld()->GetTimerManager().ClearTimer(FurnaceTimerHandle); OnCooking = false; }

}

void UFurnaceInventoryComponent::FinishSmelting()
{
	if (ItemSlots[2].Item == nullptr)
	{
		if (ItemSlots[0].Item != nullptr)
		{
			ItemSlots[2].Item = ItemSlots[0].Item->SmeltItemResult.Item;
			ItemSlots[2].Quantity = 1;
		}
	}

	else
	{
		ItemSlots[2].Quantity += 1;
	}

	SubtractSlot(0);
	PercentageOfMelt = 0;

	if (ItemSlots[0].Quantity <= 0 || ItemSlots[2].Quantity >= ItemSlots[2].Item->MaxStack)
	{
		bIsSmeltableItem = false;
		OnCooking = false;
	}

	OnItemUpdated.Broadcast();
}

void UFurnaceInventoryComponent::SubtractSlot(int32 SlotIndex)
{
	ItemSlots[SlotIndex].Quantity--;
	if (ItemSlots[SlotIndex].Quantity == 0) ItemSlots[SlotIndex].Item = nullptr;
}

void UFurnaceInventoryComponent::ResetSmeltItem()
{
	PercentageOfMelt = 0;
	bIsSmeltableItem = false;
	SmeltableDensity = 0;
	SmeltableItemSlot = FItemSlot{ };
}