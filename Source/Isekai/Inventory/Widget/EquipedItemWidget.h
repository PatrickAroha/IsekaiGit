// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Isekai/Inventory/EquipmentComponent.h"
#include "EquipedItemWidget.generated.h"

class USlotInventory;
class UEquipmentComponent;

UCLASS()
class ISEKAI_API UEquipedItemWidget : public UUserWidget
{
	GENERATED_BODY()

	public:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI | Inventory")
		TArray<TObjectPtr<USlotInventory>> Slots;

		UPROPERTY(EditAnywhere, Category = "UI | Inventory")
		TSubclassOf<UUserWidget> SlotClass;

		UPROPERTY(meta=(BindWidget))
		UImage* ItemIcon;
	
		UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
		UEquipmentComponent* EquipmentComponent;

		
	
	protected:


	public:
	void NativeConstruct();
	UFUNCTION()
		void UpdateWidget(FItemSlot& Item);
	
};





