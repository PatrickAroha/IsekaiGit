#include "IsekaiPlayerController.h"

#include "EnhancedInputComponent.h"
#include "IsekaiCharacter.h"
#include "Isekai/Core/PlayerHUD.h"

void AIsekaiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(InventoryAction, ETriggerEvent::Started, this, &AIsekaiPlayerController::ToggleInventory);
	}
}

void AIsekaiPlayerController::ToggleInventory()
{
	if (APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD()))
	{
		if (AIsekaiCharacter* Char = Cast<AIsekaiCharacter>(GetPawn()))
		{
			PlayerHUD->ToggleInventory(Char->InventoryComponent, Char->EquipmentComponent);
		}
	}
}



/*
void AIsekaiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Garante que é o personagem certo
	if (AIsekaiCharacter* Char = Cast<AIsekaiCharacter>(InPawn))
	{
		if (APlayerHUD* HUD = Cast<APlayerHUD>(GetHUD()))
		{
			HUD->CreateHUDWidget();
		}
	}
}
*/
