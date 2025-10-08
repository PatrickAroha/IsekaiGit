#include "BaseTableCraft.h"
#include "CraftWidget.h"
#include "Components/ScrollBox.h"
#include "Engine/AssetManager.h"
#include "Slate/SGameLayerManager.h"


ABaseTableCraft::ABaseTableCraft(): CraftingStationType()
{
	PrimaryActorTick.bCanEverTick = false;

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	RootComponent = TableMesh;
}

void ABaseTableCraft::BeginPlay()
{
	Super::BeginPlay();
	
	LoadCraftRecipes();
	
}

void ABaseTableCraft::LoadCraftRecipes()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	if (!AssetManager.IsInitialized()) return;

	TArray<FPrimaryAssetId> KardDataAssetId;

	AssetManager.GetPrimaryAssetIdList(PrimaryPDACraft, KardDataAssetId);
	TArray<FSoftObjectPath> KardDataPaths;
	for (const FPrimaryAssetId& AssetId : KardDataAssetId)
	{
		KardDataPaths.Add(AssetManager.GetPrimaryAssetPath(AssetId));
	}

	FStreamableManager& StreamableManager = AssetManager.GetStreamableManager();
	AssetLoadingHandle = StreamableManager.RequestAsyncLoad(KardDataPaths, FStreamableDelegate::CreateUObject(this, &ThisClass::OnAssetLoaded));
}

void ABaseTableCraft::OnAssetLoaded()
{
	if (AssetLoadingHandle.IsValid())
	{
		TArray<UObject*> LoadedAssets;

		AssetLoadingHandle->GetLoadedAssets(AvailableRecipes);

		for (UObject* LoadedAsset : LoadedAssets)
		{
			if (UPDA_CraftItem* CraftItem = Cast<UPDA_CraftItem>(LoadedAsset))
			{
				AvailableRecipes.Add(CraftItem);
			}
		}
	}
	AssetLoadingHandle.Reset();
	
}

void ABaseTableCraft::Interact_Implementation(AIsekaiCharacter* Player)
{

	if (!CraftWidgetClass) return;

	PlayerUnlockedCrafts = 	Player->UnlockedCrafts;
	
	UCraftWidget* CraftUI = CreateWidget<UCraftWidget>(GetWorld(), CraftWidgetClass);
	
	CraftUI->InventoryComponent = Player->InventoryComponent;
	
	ExposeUnlockedCrafts(CraftUI);
	
	if (CraftUI)
	{
		CraftUI->AddToViewport();

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(CraftUI->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputMode);
		}
	}
}

void ABaseTableCraft::BeginFocus_Implementation()
{
	IInteractInterface::BeginFocus_Implementation();

	if (TableMesh)
	{
		TableMesh->SetRenderCustomDepth(true);
	}
}

void ABaseTableCraft::EndFocus_Implementation()
{
	if (TableMesh)
	{
		TableMesh->SetRenderCustomDepth(false);
	}
}

void ABaseTableCraft::ExposeUnlockedCrafts(UCraftWidget* CraftUI)
{
	if (!PlayerUnlockedCrafts.IsEmpty())
	{
		for (int32 i = 0; i < AvailableRecipes.Num(); i++)
		{
			if (AvailableRecipes[i]->CraftTableType == CraftingStationType)
			{
				if (PlayerUnlockedCrafts.Contains(AvailableRecipes[i]->Item) && PlayerUnlockedCrafts[AvailableRecipes[i]->Item])
				{
					CraftUI->UnlockedsRecipes.AddUnique(AvailableRecipes[i]);
				}
			}
		}
		CraftUI->OnRecipesReceived();
	}
}