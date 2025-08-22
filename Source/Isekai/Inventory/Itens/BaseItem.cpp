#include "BaseItem.h"

#include "IDetailTreeNode.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseItem::ABaseItem()
{
	
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
}

#if WITH_EDITOR
void ABaseItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, ItemInfo))
		if (ItemInfo) Mesh->SetStaticMesh(ItemInfo->WorldMesh);
	
}
#endif

void ABaseItem::Interact_Implementation(AActor* Player)
{
	if (UInventoryComponent* Inv = Player->FindComponentByClass<UInventoryComponent>())
	{
		if (int32 StackQuantity = Inv->AddItem(ItemInfo, Quantity); StackQuantity <= 0)
		{
			Destroy();
		}
		else
		{
			Quantity = StackQuantity;
		}
	}
}


void ABaseItem::BeginFocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}


void ABaseItem::EndFocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}


void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





