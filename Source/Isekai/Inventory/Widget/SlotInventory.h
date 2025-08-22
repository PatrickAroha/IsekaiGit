#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SlotInventory.generated.h"

class UPDA_Master;

UCLASS()
class ISEKAI_API USlotInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotIndex;

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UTextBlock* SlotIndexText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* ItemIconTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UPDA_Master* ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32 Quantity;
};
