#include "LevelComponent.h"

ULevelComponent::ULevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
	XPToNextLevel = CalculateNextXPRequirement();
}

void ULevelComponent::AddXP(float Amount)
{
	CurrentXP += Amount;
	OnXPChanged.Broadcast(CurrentXP);
	
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
	OnLevelUp.Broadcast(CurrentLevel);
	OnXPChanged.Broadcast(CurrentXP);
}

float ULevelComponent::CalculateNextXPRequirement() const
{
	return FMath::RoundToFloat(BaseXP * FMath::Pow(CurrentLevel, 2.0f));
}
