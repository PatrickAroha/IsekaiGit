// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotInventory.h"
#include "Isekai/Inventory/EquipmentComponent.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/ItemStructure.h"
#include "Equipment.generated.h"


class UGridPanel;
class UEquipmentComponent;

UCLASS()
class ISEKAI_API UEquipment : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UGridPanel* InventoryGrid = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI | Inventory")
	TArray<TObjectPtr<USlotInventory>> Slots;

	UPROPERTY(EditAnywhere, Category = "UI | Inventory")
	TSubclassOf<UUserWidget> SlotClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TArray<FItemSlot> ItemSlots;
	
	UFUNCTION(BlueprintCallable)
	void InitItems(const TArray<FItemSlot>& ItemSlotsCopy);
	
	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
	UEquipmentComponent* EquipmentComponent;
	
protected:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void FillSlots();

public:
	void GenerateInventory();
	
};

