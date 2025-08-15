// Copyright Epic Games, Inc. All Rights Reserved.

#include "IsekaiGameMode.h"
#include "IsekaiCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIsekaiGameMode::AIsekaiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
