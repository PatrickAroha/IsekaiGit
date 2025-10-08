// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Isekai/CraftSystem/PDA_CraftItem.h"
#include "BaseTableCraft.generated.h"

class UCraftWidget;

UCLASS()
class ISEKAI_API ABaseTableCraft : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:

	ABaseTableCraft();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Craft")
	ECraftingStation CraftingStationType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft")
	TArray<UPDA_CraftItem*> AvailableRecipes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Craft|Mesh")
	UStaticMeshComponent* TableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft|Mesh")
	FPrimaryAssetType PrimaryPDACraft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft|UI")
	TSubclassOf<UUserWidget> CraftWidgetClass;

	TSharedPtr<FStreamableHandle> AssetLoadingHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
	TMap<FName, bool> PlayerUnlockedCrafts;
	
	UFUNCTION(BlueprintCallable, Category="Craft")
	void LoadCraftRecipes();
	void OnAssetLoaded();
	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	virtual void BeginFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;
	void ExposeUnlockedCrafts(UCraftWidget* CraftUI);

protected:
	
	virtual void BeginPlay() override;

};
