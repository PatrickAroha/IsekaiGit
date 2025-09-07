#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAtributeType : uint8
{
	Vida,
	Stamina,
	Mana,
	Attack,
	Power,
	Defense,
	Velocity,
	Jump,
	Dodge
};