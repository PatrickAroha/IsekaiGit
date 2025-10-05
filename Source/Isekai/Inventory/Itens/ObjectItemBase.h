// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectItemBase.generated.h"


UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class ISEKAI_API UObjectItemBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item")
	void Use(class AIsekaiCharacter* Player);

	virtual void Use_Implementation(AIsekaiCharacter* Player);
};
