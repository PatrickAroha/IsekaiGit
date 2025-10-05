#pragma once

#include "CoreMinimal.h"
#include "Isekai/Inventory/BaseInventoryComponent.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "ItemStructure.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPotionChanged, FItemSlot&, Item);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UEquipmentComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:

	UEquipmentComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment")
	int32 EquipmentSize = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	EItemCategory Type = EItemCategory::Misc;

	UPROPERTY()
	TArray<EItemCategory> AllowedTypes;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void EquipItem(FItemSlot& ItemSlot, int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipItem(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool HasItem(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	FItemSlot GetItemAt(int32 SlotIndex) const;

	virtual int32 UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent) override;

	virtual int32 UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent) override;

	virtual void ClearSlot(int32 Index) override;
	void NextEquipItem();

	void EquipPotion(FItemSlot& Item, int32 Index);

	virtual void Use() override;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPotionChanged OnPotionChanged;
	
	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FItemSlot ItemEquiped;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	int32 PotionEquipIndex = 2;
	
};



















