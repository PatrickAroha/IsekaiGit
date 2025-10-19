#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueSystem.h"
#include "BaseMessageWidget.generated.h"

class UTextBlock;

UCLASS()
class ISEKAI_API UBaseMessageWidget : public UUserWidget 
{
	GENERATED_BODY()
public:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock;
	
	UFUNCTION(Category = "DialogueSystem")
	void UpdateTextMessage(FText Message);
	
	void NativeConstruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	UDialogueSystem* DialogueSystem;
};