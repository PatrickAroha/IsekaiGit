#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Isekai/Interfaces/InteractInterface.h"
#include "DialogueSystem.generated.h"

class UBaseDialogueWidgetFunction;
class UBaseMessageWidget;
class AIsekaiCharacter;
class UObjectItemBase;

DECLARE_DELEGATE_OneParam(FSandMessage, FText)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UDialogueSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UDialogueSystem();
	
	FSandMessage SandMessage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Messages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> OutFunctionMessages;
	
	UPROPERTY()
	int32 MessageCounter = -1;

	UPROPERTY()
	int32 MaxMessage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FunctionMessage = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FunctionOneInteract = false;

	UPROPERTY()
	bool HasInteracted = false;

	UPROPERTY()
	bool DidOnce = false;
	
	UPROPERTY()
	AIsekaiCharacter* Player = nullptr;

	UPROPERTY()
	UBaseMessageWidget* MessageWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	TSubclassOf<UBaseMessageWidget> MessageWidgetClass;
	
	
	UFUNCTION(BlueprintCallable, Category = "DialogueSystem")
	void GenerateMessageWidget(bool ToClose);

	UFUNCTION()
	void WidgetMode();

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem")
	void StartDialogue(AIsekaiCharacter* MyPlayer);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem")
	void NextMenssage();

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem")
	void OnDialogueEnded();

protected:
	virtual void BeginPlay() override;

};
