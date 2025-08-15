#include "BaseItem.h"
#include "Isekai/Inventory/InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseItem::ABaseItem()
{
	
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
}


void ABaseItem::Interact_Implementation(AActor* Player)
{
	if (UInventoryComponent* Inv = Player->FindComponentByClass<UInventoryComponent>())
	{
		static const FString Context(TEXT("Item CollectItem"));
		if (FItem* ItemData = Inv->ItemDataTable->FindRow<FItem>(ItemRowName, Context))
		{

			if (int32 StackQuantity = Inv->AddItem(*ItemData, Quantity); StackQuantity <= 0)
			{
				Destroy();
			}
			else
			{
				Quantity = StackQuantity;
			}
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





