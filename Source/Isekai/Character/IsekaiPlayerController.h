#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IsekaiPlayerController.generated.h"

class UInputAction;

UCLASS()
class ISEKAI_API AIsekaiPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	void ToggleInventory();

//	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InventoryAction;
};