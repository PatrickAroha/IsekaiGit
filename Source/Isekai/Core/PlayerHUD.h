#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UInv;
class UInventoryComponent;
class UEquipmentComponent;

UCLASS()
class ISEKAI_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ToggleInventory(UInventoryComponent* InventoryComp, UEquipmentComponent* EquipmentComp);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInv> InventoryClass;

	UPROPERTY()
	UInv* InventoryWidget;
};