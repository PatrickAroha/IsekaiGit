// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Isekai/Interfaces/InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "BaseItem.generated.h"

UCLASS()
class ISEKAI_API ABaseItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Item")
	TObjectPtr<UPDA_Master> ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	virtual void Interact_Implementation(AActor* Player) override;
	virtual void EndFocus_Implementation() override;
	virtual void BeginFocus_Implementation() override;

	
	// Sets default values for this actor's properties
	ABaseItem();
	
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

};
