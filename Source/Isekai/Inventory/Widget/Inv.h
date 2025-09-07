// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Isekai/Inventory/EquipmentComponent.h"
#include "Inv.generated.h"

class UEquipment;
class UBaseInventory;


UCLASS()
class ISEKAI_API UInv : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory", meta = (ExposeOnSpawn))
	UEquipmentComponent* EquipmentComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	TObjectPtr<UBaseInventory> InventoryWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	TObjectPtr<UEquipment> EquipmentWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UBaseInventory> InventoryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UEquipment> EquipmentClass;

protected:
	
	virtual void NativeConstruct() override;
	
};
