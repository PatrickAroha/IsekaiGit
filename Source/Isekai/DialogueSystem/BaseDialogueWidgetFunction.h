#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseDialogueWidgetFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReturnMessage);

UCLASS()
class ISEKAI_API UBaseDialogueWidgetFunction : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FReturnMessage ReturnMessage;

	UFUNCTION(BlueprintCallable)
	void CallBack();

protected:
	virtual void NativeConstruct() override;
	
	void WidgetMode();
};
