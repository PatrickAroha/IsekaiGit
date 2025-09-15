#include "LevelComponent.h"

ULevelComponent::ULevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULevelComponent::AddXP(float Amount)
{
	CurrentXP += Amount;
	OnXPChanged.Broadcast(CurrentXP);

	// Loop pra lidar com casos de ganhar muito XP de uma vez
	while (CurrentXP >= XPToNextLevel)
	{
		CurrentXP -= XPToNextLevel;
		LevelUp();
	}
}

void ULevelComponent::LevelUp()
{
	CurrentLevel++;
	XPToNextLevel = CalculateNextXPRequirement();

	// Notifica quem estiver ouvindo
	OnLevelUp.Broadcast(CurrentLevel);
}

float ULevelComponent::CalculateNextXPRequirement() const
{
	// Exemplo simples de curva de XP
	return FMath::RoundToFloat(XPToNextLevel * XPScale);
}