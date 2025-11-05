#pragma once

#include "CoreMinimal.h"
#include "NPCFunctions.h"
#include "GameFramework/Character.h"
#include "Isekai/Interfaces/InteractInterface.h"
#include "Isekai/MissionsSystem/MissionComponent.h"
#include "BaseNPC.generated.h"

class UBaseDialogueWidgetFunction;
class UDialogueSystem;

UENUM(BlueprintType)
enum class NPCType : uint8
{
	None      UMETA(DisplayName = "none"),
	Merchant  UMETA(DisplayName = "Merchant")
};

UCLASS()
class ISEKAI_API ABaseNPC : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	ABaseNPC();
	void ExecuteDialogueFunction();
	void OnDialogueEnded();

protected:

	UPROPERTY()
	AIsekaiCharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	NPCType NPCType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="NPCType == NPCType::Merchant"))
	TArray<FItemSlot> ItemForSale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flow")
	TArray<UPDA_MissionInfo*> Quests;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest")
	FGameplayTag NPCQuestTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UNPCFunctions> FunctionClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDialogueSystem* DialogueSystem;


	virtual void BeginPlay() override;
	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	virtual void BeginFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;
};
