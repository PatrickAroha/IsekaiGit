#pragma once

#include "CoreMinimal.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "FurnaceInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUpdated);

class UGridPanel;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UFurnaceInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemUpdated OnItemUpdated;
	
	virtual void DropItem(int32 Index, int32 Quantity);
	
	UFurnaceInventoryComponent();

	FTimerHandle FurnaceTimerHandle;

	float SmeltDuration = 0;
	float SmeltFrequency = 0.1;
	float PercentageOfMelt = 0;		// Progresso de cozimento
	float CurrentEnergy = 0;		// Quantidade de combustivel
	float FuelPotency = 0;
	
	int32 SmeltableDensity = 0;		// Resistencia do Minerio
	int32 FuelPower = 0;			// Potencia do combustivel
	int32 MaxEnergy = 0;

	bool OnCooking = false;
	bool bIsFuelItem = false;
	bool bIsSmeltableItem = false;
	
	FItemSlot FuelItemSlot;
	FItemSlot SmeltableItemSlot;
	
protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateItem(int32 SlotIndex);
	void SmeltableItem(int32 SlotIndex);
	void FuelItem(int32 SlotIndex);
	void FinishSmelting();
	void Melt();
	void CalculateTimeOfCook();
	void Cooking();
	void ConsumeFuel();
	void SubtractSlot(int32 SlotIndex);
	void ResetSmeltItem();
};