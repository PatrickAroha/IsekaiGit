// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseInventoryComponent.generated.h"


struct FItemSlot;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UBaseInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBaseInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<FItemSlot> ItemSlots;
	
protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual int32 UpdateSlotLeftClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable)
	virtual int32 UpdateSlotRightClick(FItemSlot& GetItemSlot, int32 NewIndex, UBaseInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable)
	void ClearSlot(int32 Index);
};
