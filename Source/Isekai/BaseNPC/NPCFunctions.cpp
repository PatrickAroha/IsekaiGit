// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCFunctions.h"
#include "BaseNPC.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Character/IsekaiCharacter.h"

void UNPCFunctions::StartFunction(AIsekaiCharacter* Player, ABaseNPC* Caller)
{
	PlayerRef = Player;
	CallerRef = Caller;

	ExecuteFunction();
}

void UNPCFunctions::ExecuteFunction_Implementation()
{
	
}

void UNPCFunctions::EndExecute()
{
	if (CallerRef)
	CallerRef->OnDialogueEnded();
}

UWorld* UNPCFunctions::GetWorld() const
{
	if (PlayerRef)
	return PlayerRef->GetWorld();
	return nullptr;
}


