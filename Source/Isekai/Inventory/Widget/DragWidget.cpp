// Fill out your copyright notice in the Description page of Project Settings.


#include "DragWidget.h"

#include "Isekai/Inventory/PDA_Master.h"

void UDragWidget::UpdateWidget(FItemSlot& NewSlot, int32 DragWidget)
{
	ItemSlot = NewSlot;
	
	Text->SetText(FText::AsNumber(DragWidget));
	Texture = NewSlot.Item->Icon;
	DragImage->SetBrushFromTexture(Texture);
}
