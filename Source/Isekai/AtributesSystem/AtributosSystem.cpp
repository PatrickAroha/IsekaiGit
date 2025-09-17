#include "AtributosSystem.h"

#include "LevelComponent.h"


UAtributosSystem::UAtributosSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtributosSystem::SetValue(EAtributeType Atribute, int32 NewValue)
{
	if (Attributes.Contains(Atribute))
		Attributes[Atribute] = NewValue;
	OnAttributesUpdated.Broadcast(this);
}

void UAtributosSystem::AddBonusValue(EAtributeType Atribute, int32 Amount)
{
	if (Attributes.Contains(Atribute))
		Attributes[Atribute] += Amount;
	OnAttributesUpdated.Broadcast(this);
}

void UAtributosSystem::RemoveValue(EAtributeType Atribute, int32 Amount)
{
	if (Attributes.Contains(Atribute))
		Attributes[Atribute] = FMath::Max(0, Attributes[Atribute] - Amount);
	OnAttributesUpdated.Broadcast(this);
}

int32 UAtributosSystem::GetValue(EAtributeType Atribute) const
{
	if (Attributes.Contains(Atribute))
		return Attributes[Atribute];
	return 0;
}

void UAtributosSystem::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (ULevelComponent* LevelComp = Owner->FindComponentByClass<ULevelComponent>())
		{
			// Faz o bind no evento de LevelUp
			LevelComp->OnLevelUp.AddDynamic(this, &UAtributosSystem::HandleLevelUp);
		}
	}
	
}

void UAtributosSystem::HandleLevelUp(int32 NewLevel)
{

	AddBonusValue(EAtributeType::Attack, 10);
	
}

void UAtributosSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


