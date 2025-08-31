#include "DragToggle.h"
#include "GetWidgetMouseClick.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GetWidgetMouseClick.h"

#include "Blueprint/UserWidget.h"

void UDragToggle::DragToggleStart(UUserWidget* InWidget, FItemSlot GetItemSlot, int32 GetLastIndex, UInventoryComponent* InventoryComponent)
{
	if (!InWidget) return;
	if (GetItemSlot.Quantity <= 0)
	{
		DragToggleCancel();
		return;
	}
	
	DragWidget = InWidget;
	ItemSlot = GetItemSlot;
	LastIndex = GetLastIndex;
	GetInventoryComponent = InventoryComponent;
	DragToggleUpdateWidgetLocation();
}

void UDragToggle::DragToggleDrop(FKey MouseEvent, int32 NewIndex, UInventoryComponent* NewInventoryComponent)
{
	if (DragToggleIsActive())
	{
		if (APlayerController* PC = GetLocalPlayer()->GetPlayerController(GetWorld()))
		{
			bool bIsSlotInventory = false;
	
			if(UWidget* HitWidget = UGetWidgetMouseClick::GetWidgetUnderCursor(PC, bIsSlotInventory))
			{
				
			//	if (HitWidget->GetName() == "W_SlotInventory")
				{
					if (MouseEvent == EKeys::LeftMouseButton)
					{
						int32 DragQuantity = GetInventoryComponent->UpdateSlotLeftClick(ItemSlot, NewIndex, NewInventoryComponent);
						if (DragQuantity <= 0) DragToggleCancel();
						ItemSlot.Quantity = DragQuantity;
						DragToggleUpdateWidgetLocation();
						return;
					//	DragToggleCancel();
					}
					if (MouseEvent == EKeys::RightMouseButton)
					{
						UE_LOG(LogTemp, Log, TEXT("Clique DIREITO detectado"));
					}
				}
			}
		}
	}
	else
	{
		DragWidget = CreateWidget(UUserWidget* )
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

