// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Isekai/TableBase/TableBase.h"
#include "GameFramework/Actor.h"
#include "Isekai/TableBase/CraftSystem/PDA_CraftItem.h"
#include "BaseTableCraft.generated.h"

class UCraftWidget;

UCLASS()
class ISEKAI_API ABaseTableCraft : public ATableBase
{
	GENERATED_BODY()

public:

	ABaseTableCraft();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Craft")
	ECraftingStation CraftingStationType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft")
	TArray<UPDA_CraftItem*> AvailableRecipes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft|Mesh")
	FPrimaryAssetType PrimaryPDACraft;

	TSharedPtr<FStreamableHandle> AssetLoadingHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
	TMap<FName, bool> PlayerUnlockedCrafts;
	
	UFUNCTION(BlueprintCallable, Category="Craft")
	void LoadCraftRecipes();
	void OnAssetLoaded();
	void ExposeUnlockedCrafts(UCraftWidget* CraftUI);
	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	virtual void BeginFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;

protected:
	
	virtual void BeginPlay() override;

};
