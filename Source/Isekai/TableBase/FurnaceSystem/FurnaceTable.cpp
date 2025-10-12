#include "FurnaceTable.h"

#include "FurnaceInventoryComponent.h"
#include "FurnaceWidget.h"
#include "Isekai/Character/IsekaiCharacter.h"


AFurnaceTable::AFurnaceTable()
{
	PrimaryActorTick.bCanEverTick = false;
	FurnaceInventory = CreateDefaultSubobject<UFurnaceInventoryComponent>(TEXT("FurnaceInventory"));
}

void AFurnaceTable::Interact_Implementation(AIsekaiCharacter* Player)
{
	Super::Interact_Implementation(Player);

	if (!WidgetClass) return;
	
	UFurnaceWidget* FurnaceWidget = CreateWidget<UFurnaceWidget>(GetWorld(), WidgetClass);
	if (!FurnaceWidget) return;
	
	FurnaceWidget->InventoryComponent = FurnaceInventory;
	FurnaceWidget->PlayerInventoryComponent = Player->InventoryComponent;
	FurnaceWidget->OwnerTable = this;
	FurnaceWidget->AddToViewport();
}

void AFurnaceTable::BeginPlay()
{
	Super::BeginPlay();
}

void AFurnaceTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

