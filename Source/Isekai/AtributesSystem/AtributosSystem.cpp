#include "AtributosSystem.h"

#include "LevelComponent.h"
#include "StatusComponent.h"
#include "Isekai/Character/IsekaiCharacter.h"


UAtributosSystem::UAtributosSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtributosSystem::SetValue(EAtributeType Atribute, float NewValue)
{
	if (Attributes.Contains(Atribute))
		Attributes[Atribute] = NewValue;

	OnAttributesUpdated.Broadcast(this, Atribute, NewValue);
}

void UAtributosSystem::ChangeBonusValue(EAtributeType Atribute, float Amount)
{
	
	if (!Attributes.Contains(Atribute)) return;
	
	Attributes[Atribute] += Amount;

	OnAttributesUpdated.Broadcast(this, Atribute, Amount);
	
}

float UAtributosSystem::GetValue(EAtributeType Atribute) const
{
	if (Attributes.Contains(Atribute))
		return Attributes[Atribute];
	return 0;
}

void UAtributosSystem::BeginPlay()
{
	Super::BeginPlay();
	
	BaseAttributes = Attributes;
	
	if (AActor* Owner = GetOwner())
	{
		if (ULevelComponent* LevelComp = Owner->FindComponentByClass<ULevelComponent>())
		{
			LevelComp->OnLevelUp.AddDynamic(this, &UAtributosSystem::HandleLevelUp);
		}
	}
}

void UAtributosSystem::HandleLevelUp(int32 NewLevel)
{
	ChangeBonusValue(EAtributeType::Vida, 10);
	ChangeBonusValue(EAtributeType::Mana, 10);
	ChangeBonusValue(EAtributeType::Stamina, 10);
	ChangeBonusValue(EAtributeType::Attack, 10);
	ChangeBonusValue(EAtributeType::Defense, 10);
	ChangeBonusValue(EAtributeType::Power, 10);
	ChangeBonusValue(EAtributeType::Velocity, 10);
	ChangeBonusValue(EAtributeType::Dodge, 10);
	ChangeBonusValue(EAtributeType::Jump, 10);
}

void UAtributosSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


