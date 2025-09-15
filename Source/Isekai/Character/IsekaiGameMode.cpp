// Copyright Epic Games, Inc. All Rights Reserved.

#include "IsekaiGameMode.h"
#include "IsekaiCharacter.h"
#include "IsekaiPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AIsekaiGameMode::AIsekaiGameMode()
{
	DefaultPawnClass = AIsekaiCharacter::StaticClass();
	PlayerControllerClass = AIsekaiPlayerController::StaticClass();
}
