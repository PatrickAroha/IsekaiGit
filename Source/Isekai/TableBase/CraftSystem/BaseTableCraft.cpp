#include "BaseTableCraft.h"
#include "CraftWidget.h"
#include "Engine/AssetManager.h"


ABaseTableCraft::ABaseTableCraft(): CraftingStationType(), AssetLoadingHandle(nullptr)
{
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

void ABaseTableCraft::Interact_Implementation(AIsekaiCharacter* Player)
{
	if (!WidgetClass) return;

	PlayerUnlockedCrafts = 	Player->UnlockedCrafts;
	
	UCraftWidget* CraftUI = CreateWidget<UCraftWidget>(GetWorld(), WidgetClass);
	
	CraftUI->InventoryComponent = Player->InventoryComponent;
	
	ExposeUnlockedCrafts(CraftUI);
	
	if (CraftUI)
	{
		CraftUI->AddToViewport();
	}
}

void ABaseTableCraft::BeginFocus_Implementation()
{
	Super::BeginFocus_Implementation();
}

void ABaseTableCraft::EndFocus_Implementation()
{
	Super::EndFocus_Implementation();
}

