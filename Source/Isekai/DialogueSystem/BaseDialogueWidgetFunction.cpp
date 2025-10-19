#include "BaseDialogueWidgetFunction.h"


void UBaseDialogueWidgetFunction::CallBack()
{
	ReturnMessage.Broadcast();
}

void UBaseDialogueWidgetFunction::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetMode();
	
}

void UBaseDialogueWidgetFunction::WidgetMode()
{
	if (GetOwningPlayer()) return;
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputMode);
	PC->FlushPressedKeys();
	PC->bShowMouseCursor = true;
}