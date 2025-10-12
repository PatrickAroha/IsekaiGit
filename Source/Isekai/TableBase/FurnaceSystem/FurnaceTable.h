#pragma once

#include "CoreMinimal.h"
#include "Isekai/TableBase/TableBase.h"
#include "FurnaceTable.generated.h"

class UFurnaceInventoryComponent;

UCLASS()
class ISEKAI_API AFurnaceTable : public ATableBase
{
	GENERATED_BODY()

public:
	
	AFurnaceTable();
	
	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Furnace")
	UFurnaceInventoryComponent* FurnaceInventory;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
