// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotInventory.h"
#include "Blueprint/UserWidget.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class ISEKAI_API UDragWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateWidget(FItemSlot& NewSlot, int32 DragWidget);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(ExposeOnSpawn = true))
	int32 LastIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TObjectPtr<USlotInventory> LastSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(ExposeOnSpawn = true))
	FItemSlot ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta=(ExposeOnSpawn = true))
	UTexture2D* Texture;

	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadOnly)
	UTextBlock* Text;

	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadOnly)
	UImage* DragImage;
	
};
