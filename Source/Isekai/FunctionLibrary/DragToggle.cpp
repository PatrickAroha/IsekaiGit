#include "GetWidgetMouseClick.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GetWidgetMouseClick.h"
#include "DragToggle.h"
#include "Blueprint/UserWidget.h"

void UDragToggle::DragToggleStart(UUserWidget* InWidget, FItemSlot GetItemSlot, int32 GetLastIndex)
{
	if (!InWidget) return;
	
	DragWidget = InWidget;
	ItemSlot = GetItemSlot;
	LastIndex = GetLastIndex;
}

bool UDragToggle::DragToggleDrop()
{
	if (DragToggleIsActive())
	{
		if (APlayerController* PC = GetLocalPlayer()->GetPlayerController(GetWorld()))
		{
			bool bIsSlotInventory = false;
			
			if(UWidget* HitWidget = UGetWidgetMouseClick::GetWidgetUnderCursor(PC, bIsSlotInventory))
			{
				if (HitWidget->GetName() == "W_SlotInventory")
				{
					
				}
			}
		}
	}
	return true;
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

bool UDragToggle::DragToggleIsActive()
{
	if (!DragWidget) return false;
	if (ItemSlot.Quantity == 0) return false;
	
	return true;
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
			DragWidget->SetPositionInViewport(MousePos, false);
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

