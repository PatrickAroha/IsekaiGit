#include "BaseMessageWidget.h"

#include "Components/TextBlock.h"

void UBaseMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DialogueSystem)
	{
		DialogueSystem->SandMessage.BindUFunction(this, FName("UpdateTextMessage"));
	}
	
}

void UBaseMessageWidget::UpdateTextMessage(FText Message) 
{
	if (TextBlock)
	{
		TextBlock->SetText(Message);
	}
}
