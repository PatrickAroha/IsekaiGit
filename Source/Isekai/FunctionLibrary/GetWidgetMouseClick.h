// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetWidgetMouseClick.generated.h"

/**
 * 
 */
UCLASS()
class ISEKAI_API UGetWidgetMouseClick : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="UI")
	static UUserWidget* GetWidgetUnderCursor(APlayerController* PC, bool& bIsSlotInventory);
};
