#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class USlotInventory;
class UGridPanel;
class UButton;

UCLASS()
class ISEKAI_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* CloseWidget;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USlotInventory*> Slots;
	
	virtual void NativeConstruct() override;

	void GenerateInventory();
	
};




