// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Isekai/CraftSystem/PDA_CraftItem.h"
#include "BaseTableCraft.generated.h"

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

	TSharedPtr<FStreamableHandle> AssetLoadingHandle;
	
	UFUNCTION(BlueprintCallable, Category="Craft")
	void LoadCraftRecipes();
	void OnAssetLoaded();
	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	
protected:
	
	virtual void BeginPlay() override;

};
