// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Isekai/Inventory/BaseInventoryComponent.h"
#include "ItemStructure.h"
#include "EquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UEquipmentComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:

	UEquipmentComponent();

	// Quantos slots o equipamento vai ter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment")
	int32 EquipmentSize = 4;

	// Inicializa os slots vazios
	virtual void BeginPlay() override;

	// Equipa item num slot específico
	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool EquipItem(FItemSlot& ItemSlot, int32 SlotIndex);

	// Remove item do slot
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipItem(int32 SlotIndex);

	// Verifica se o slot tem item
	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool HasItem(int32 SlotIndex) const;

	// Retorna o item no slot
	UFUNCTION(BlueprintCallable, Category="Equipment")
	FItemSlot GetItemAt(int32 SlotIndex) const;
};