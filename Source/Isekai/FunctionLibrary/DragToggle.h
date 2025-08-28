#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Isekai/Inventory/ItemStructure.h"
#include "DragToggle.generated.h"

UCLASS()
class ISEKAI_API UDragToggle : public ULocalPlayerSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Drag")
	void DragToggleStart(UUserWidget* InWidget, FItemSlot ItemSlot, int32 LastIndex);
	
	UFUNCTION(BlueprintCallable, Category="Drag")
	bool DragToggleDrop();
	
	UFUNCTION(BlueprintCallable, Category="Drag")
	void DragToggleCancel();

	UFUNCTION(BlueprintCallable, Category="Drag")
	bool DragToggleIsActive();

	UFUNCTION(BlueprintCallable, Category="Drag")
	void DragToggleUpdateWidgetLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FItemSlot ItemSlot;

	virtual	void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; }

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	int32 LastIndex;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	int32 LastQuantity;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	int32 Index;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	UUserWidget* DragWidget;
	
};
