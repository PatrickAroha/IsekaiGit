#include "EquipedItemWidget.h"

void UEquipedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>();
			if (EquipmentComponent)
			{
				EquipmentComponent->OnPotionChanged.AddDynamic(this, &UEquipedItemWidget::UpdateWidget);

				// já mostra o item inicial, se existir
				if (EquipmentComponent->ItemEquiped.Item)
				{
					UpdateWidget(EquipmentComponent->ItemEquiped);
				}
			}
		}
	}
}

void UEquipedItemWidget::UpdateWidget(FItemSlot& Item)
{
	if (Item.Item && Item.Item->Icon)
	ItemIcon->SetBrushFromTexture(Item.Item->Icon);
	else
	ItemIcon->SetBrushFromTexture(nullptr);
}
