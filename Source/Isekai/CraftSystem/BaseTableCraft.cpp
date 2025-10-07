#include "BaseTableCraft.h"
#include "Engine/AssetManager.h"


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

	UE_LOG(LogTemp, Warning, TEXT("[Craft] Interagindo com bancada: %s"), *UEnum::GetValueAsString(CraftingStationType));

	// Exemplo: mostrar receitas disponíveis
	for (UPDA_CraftItem* Recipe : AvailableRecipes)
	{
		if (!Recipe) continue;

		UE_LOG(LogTemp, Warning, TEXT("[Craft] Receita disponível: %s (Resultado: %s)"),
			*Recipe->GetName(),
			*Recipe->CraftResult.Item->GetName());
	}
	
}
