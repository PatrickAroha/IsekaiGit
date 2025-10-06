#include "AtributosSystem.h"

#include "LevelComponent.h"
#include "StatusComponent.h"
#include "Isekai/Character/IsekaiCharacter.h"


UAtributosSystem::UAtributosSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtributosSystem::SetValue(EAtributeType Atribute, int32 NewValue)
{
	if (Attributes.Contains(Atribute))
		Attributes[Atribute] = NewValue;

	OnAttributesUpdated.Broadcast(this, Atribute, NewValue);
}

void UAtributosSystem::AddBonusValue(EAtributeType Atribute, float Amount)
{
	if (!Attributes.Contains(Atribute)) return;
	
	if (Amount > 1)
	{
		Attributes[Atribute] += Amount;
		OnAttributesUpdated.Broadcast(this, Atribute, Amount);
	}
	else
	{
		if (BaseAttributes.Contains(Atribute))
		{
			Attributes[Atribute] +=  BaseAttributes[Atribute] * Amount;
			OnAttributesUpdated.Broadcast(this, Atribute, Amount);
		}
	}
}

void UAtributosSystem::RemoveValue(EAtributeType Atribute, float Amount)
{
	if (!Attributes.Contains(Atribute)) return;

	if (Amount > 1)
	{
		Attributes[Atribute] = FMath::Max(0.0f, Attributes[Atribute] - Amount);
		OnAttributesUpdated.Broadcast(this, Atribute, -Amount);
	}
	else
	{
		if (BaseAttributes.Contains(Atribute))
		{
			float RemoveAmount = BaseAttributes[Atribute] * Amount;
			Attributes[Atribute] = FMath::Max(0.0f, Attributes[Atribute] - RemoveAmount);
			OnAttributesUpdated.Broadcast(this, Atribute, -RemoveAmount);
		}
	}
}

int32 UAtributosSystem::GetValue(EAtributeType Atribute) const
{
	if (Attributes.Contains(Atribute))
		return Attributes[Atribute];
	return 0;
}

void UAtributosSystem::BeginPlay()
{
	BaseAttributes = Attributes;
	Super::BeginPlay();

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

	AddBonusValue(EAtributeType::Attack, 10);
	
}

void UAtributosSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


