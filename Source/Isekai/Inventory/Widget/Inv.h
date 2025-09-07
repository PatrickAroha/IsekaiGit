#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Isekai/Inventory/EquipmentComponent.h"
#include "Inv.generated.h"

class UAtributs;
class UCanvasPanel;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	TObjectPtr<UAtributs> AtributsWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(meta = (BindWidget))
	UEquipment* W_Equipment;

	UPROPERTY(meta = (BindWidget))
	UBaseInventory* W_BaseInventory;

	UPROPERTY(meta = (BindWidget))
	UAtributs* W_Atributs;


protected:
	
	virtual void NativeConstruct() override;
	
};
