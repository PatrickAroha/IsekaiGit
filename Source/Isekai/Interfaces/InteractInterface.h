// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Isekai/Inventory/ItemStructure.h"
#include "InteractInterface.generated.h"

class ABaseItem;
class AIsekaiCharacter;
class UBaseInventoryComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ISEKAI_API IInteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AIsekaiCharacter* Player);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginFocus();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndFocus();
	
};
