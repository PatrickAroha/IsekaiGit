#include "DragToggle.h"

#include <rapidjson/internal/meta.h>

#include "GetWidgetMouseClick.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Isekai/Inventory/Widget/DragWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GetWidgetMouseClick.h"
#include "ToolContextInterfaces.h"

#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "Isekai/Inventory/Widget/DragWidget.h"

void UDragToggle::DragToggleStart(UDragWidget* GetDragWidget, UBaseInventoryComponent* InventoryComponent, FKey MouseButton)
{
	
	if (GetDragWidget->ItemSlot.Quantity <= 0)
	{
		DragToggleCancel();
		return;
	}
	
	if (MouseButton == EKeys::LeftMouseButton)
	{
		DragWidget = GetDragWidget;
		Texture = GetDragWidget->Texture;
		ItemSlot = GetDragWidget->ItemSlot;
		LastIndex = GetDragWidget->LastIndex;
		GetInventoryComponent = InventoryComponent;
		CreateDragWidget();
		DragToggleUpdateWidgetLocation();
		InventoryComponent->ClearSlot(LastIndex);
	}
	
	if (MouseButton == EKeys::RightMouseButton)
	{
		DragWidget = GetDragWidget;
		Texture = GetDragWidget->Texture;

		if (GetDragWidget->ItemSlot.Quantity % 2 == 0)
			ItemSlot.Quantity = GetDragWidget->ItemSlot.Quantity/2;
		else
			ItemSlot.Quantity = (GetDragWidget->ItemSlot.Quantity/2 + 1);
		
		ItemSlot.Item = GetDragWidget->ItemSlot.Item;
		LastIndex = GetDragWidget->LastIndex;
		GetInventoryComponent = InventoryComponent;
		CreateDragWidget();
		DragToggleUpdateWidgetLocation();
		InventoryComponent->ItemSlots[LastIndex].Quantity = (GetInventoryComponent->ItemSlots[LastIndex].Quantity/2);
	}
}

void UDragToggle::DragToggleDrop(FKey MouseEvent, int32 NewIndex, UBaseInventoryComponent* NewInventoryComponent)
{
	if (DragToggleIsActive())
	{
		if (!NewInventoryComponent) return;
		
		if (APlayerController* PC = GetLocalPlayer()->GetPlayerController(GetWorld()))
		{
			bool bIsSlotInventory = false;

			if (UWidget* HitWidget = UGetWidgetMouseClick::GetWidgetUnderCursor(PC, bIsSlotInventory))
			{

				if (HitWidget)
				{

					if (MouseEvent == EKeys::LeftMouseButton)
					{

						
						int32 DragQuantity = NewInventoryComponent->UpdateSlotLeftClick(ItemSlot, NewIndex, NewInventoryComponent);
						
						if (DragQuantity <= 0) { DragToggleCancel(); return; }
						
						ItemSlot.Quantity = DragQuantity;
						
						if (DragWidget)
							DragWidget->UpdateWidget(ItemSlot, DragQuantity);
						
						return;
					}

					if (MouseEvent == EKeys::RightMouseButton)
					{
						int32 DragQuantity = NewInventoryComponent->UpdateSlotRightClick(ItemSlot, NewIndex, NewInventoryComponent);
						
						if (DragQuantity <= 0) { DragToggleCancel(); return; }
						
						ItemSlot.Quantity = DragQuantity;
						
						if (DragWidget)
							DragWidget->UpdateWidget(ItemSlot, DragQuantity);
						
					}
				}
			}
		}
	}
}

void UDragToggle::DragToggleCancel()
{
	if (DragToggleIsActive())
	{
		DragWidget->RemoveFromParent();
		DragWidget = nullptr;
		LastIndex = 0;
		LastQuantity = 0;
	} 
}

void UDragToggle::DragToggleUpdateWidgetValues(int32 CurrentDragQuantity)
{
	if (!DragWidget) return;
	if (CurrentDragQuantity <= 0)
	{
		DragToggleCancel();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentDragQuantity);
}

bool UDragToggle::DragToggleIsActive()
{
	if (!DragWidget) return false;
	if (ItemSlot.Quantity == 0) return false;
	
	return true;
}

void UDragToggle::CreateDragWidget()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (!DragWidget->IsInViewport())
		{
			if (DragWidget)
			{
				DragWidget->LastIndex = LastIndex;
				DragWidget->ItemSlot = ItemSlot;
				DragWidget->Texture = Texture;
				DragWidget->AddToViewport();
			}
		}
	}
}

void UDragToggle::DragToggleUpdateWidgetLocation()
{
	if (!DragWidget) return;
	if (APlayerController* PC = GetLocalPlayer()->GetPlayerController(GetWorld()))
	{
		float MouseX, MouseY;
		if (PC->GetMousePosition(MouseX, MouseY))
		{
			FVector2D MousePos(MouseX, MouseY);

			// pega escala de DPI do viewport
			const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

			// corrige posição com DPI
			FVector2D CorrectedPos = MousePos / Scale;
			
			DragWidget->SetPositionInViewport(CorrectedPos, false);
		}
	}
}

void UDragToggle::Tick(float DeltaTime)
{
	if (DragToggleIsActive())
		DragToggleUpdateWidgetLocation();
}

TStatId UDragToggle::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UDragToggle, STATGROUP_Tickables);
}
