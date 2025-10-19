#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Isekai/Interfaces/InteractInterface.h"
#include "BaseNPC.generated.h"

class UDialogueSystem;

UCLASS()
class ISEKAI_API ABaseNPC : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	ABaseNPC();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDialogueSystem* DialogueSystem;
	
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	virtual void BeginFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;

	
};
