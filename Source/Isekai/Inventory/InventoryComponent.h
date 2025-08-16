// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructure.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UPDA_Master;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<FItemSlot> ItemSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize = 6;
	
	int32 AddItem(UPDA_Master* ItemData, int32 Quantity);

	int AddStack(UPDA_Master* ItemData, int32 Quantity);

	void AddUnique(UPDA_Master* ItemData, int32 Quantity);

	int NewStack(UPDA_Master* ItemData, int32 Quantity);

	void DropItem(UPDA_Master* ItemData, int32 Quantity);

	void RemoveItem();

	void SearchItem();

	void ClearInventory();
	
protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
