#include "BaseNPC.h"

#include "Isekai/DialogueSystem/DialogueSystem.h"

ABaseNPC::ABaseNPC(): DialogueSystem(nullptr)
{
	    DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueComponent"));

		GetMesh()->SetupAttachment(RootComponent);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void ABaseNPC::BeginPlay()
{

}

void ABaseNPC::Interact_Implementation(AIsekaiCharacter* MyPlayer)
{
	if (DialogueSystem && MyPlayer)
	{
		Player = MyPlayer;
		DialogueSystem->StartDialogue(Player);
	}
}

void ABaseNPC::BeginFocus_Implementation()
{

    if (GetMesh())
	{
		GetMesh()->SetRenderCustomDepth(true);
	}
}

void ABaseNPC::EndFocus_Implementation()
{
	if (GetMesh())
	{
		GetMesh()->SetRenderCustomDepth(false);
	}
}

void ABaseNPC::ExecuteDialogueFunction()
{
	UNPCFunctions* Function = NewObject<UNPCFunctions>(this, FunctionClass);
	Function->StartFunction(Player, this);
}

void ABaseNPC::OnDialogueEnded()
{
	DialogueSystem->NextMenssage();
}