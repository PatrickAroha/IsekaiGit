#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseDialogueWidgetFunction.generated.h"


UCLASS()
class ISEKAI_API UBaseDialogueWidgetFunction : public UUserWidget
{
	GENERATED_BODY()



protected:
	virtual void NativeConstruct() override;
	
	void WidgetMode();
};
