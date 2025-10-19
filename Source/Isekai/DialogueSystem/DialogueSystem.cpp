#include "DialogueSystem.h"
#include "BaseDialogueWidgetFunction.h"
#include "BaseMessageWidget.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Character/IsekaiCharacter.h"

UDialogueSystem::UDialogueSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDialogueSystem::BeginPlay()
{

}

void UDialogueSystem::StartDialogue(AIsekaiCharacter* MyPlayer)
{
	Player = MyPlayer;

	if (!Messages.Num()) return;

	MaxMessage = Messages.Num();

	MessageCounter = -1;

	if (!FunctionOneInteract) DidOnce = false;
	
	NextMenssage();
}

void UDialogueSystem::NextMenssage()
{

	if (MessageCounter + 1 == FunctionMessage && !DidOnce && FunctionMessage != -1)
		{ DidOnce = true; GenerateMessageWidget(true); DialogueFunction(); return; }

	if (HasInteracted && MessageCounter + 1 < MaxMessage && FunctionOneInteract)
	{
		GenerateMessageWidget(false);
		MessageCounter++;
		SandMessage.ExecuteIfBound(OutFunctionMessages[MessageCounter]);
		return;
	}

	if (MessageCounter + 1 < MaxMessage)
	{
		GenerateMessageWidget(false);
		MessageCounter++;
		SandMessage.ExecuteIfBound(Messages[MessageCounter]);
	}
	else
	{
		OnDialogueEnded();
	}

}

void UDialogueSystem::DialogueFunction()
{
	
	if (!Player) return;

	if (FunctionWidgetClass)
	{
		UBaseDialogueWidgetFunction* FunctionWidget = CreateWidget<UBaseDialogueWidgetFunction>(GetWorld(), FunctionWidgetClass);
		FunctionWidget->AddToViewport();
		FunctionWidget->ReturnMessage.AddDynamic(this, &UDialogueSystem::NextMenssage);
	}

}

void UDialogueSystem::OnDialogueEnded()
{
	if (MessageWidget)
	{
		if (!Player) return;
		APlayerController* PC = Cast<APlayerController>(Player->GetController());
		if (!PC) return;
		
		MessageWidget->RemoveFromParent();
		MessageWidget = nullptr;
		
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		
		HasInteracted = true;
	}
}

void UDialogueSystem::GenerateMessageWidget(bool ToClose)
{
	if (ToClose)
	{
		if (MessageWidget)
		{
			MessageWidget->SetVisibility(ESlateVisibility::Hidden);
			return;
		}
	}

	if (!MessageWidgetClass || !Player) return;
	
	if (!MessageWidget)
	{
		MessageWidget = CreateWidget<UBaseMessageWidget>(GetWorld(), MessageWidgetClass);
		MessageWidget->DialogueSystem = this;
		MessageWidget->AddToViewport();
		WidgetMode();
		return;
	}
	
	if (MessageWidget && !ToClose)
	{
		MessageWidget->SetVisibility(ESlateVisibility::Visible);
		WidgetMode();
	}
}

void UDialogueSystem::WidgetMode()
{
	if (!Player) return;
	APlayerController* PC = Cast<APlayerController>(Player->GetController());
	if (!PC) return;
	
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(MessageWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputMode);
	PC->FlushPressedKeys();
	PC->bShowMouseCursor = true;
}
