#include "StatusComponent.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

UStatusComponent::UStatusComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStatusComponent::BeginPlay()
{
    Super::BeginPlay();

    if (AActor* Owner = GetOwner())
    {
        AtributosSystem = Owner->FindComponentByClass<UAtributosSystem>();
        if (AtributosSystem)
        {
            BaseAttributes = AtributosSystem->BaseAttributes;
            Health  = GetMax(EAtributeType::Vida);
            Stamina = GetMax(EAtributeType::Stamina);
            Mana    = GetMax(EAtributeType::Mana);

            AtributosSystem->OnAttributesUpdated.AddDynamic(this, &UStatusComponent::HandleAttributesUpdated);
        }
    }
}

void UStatusComponent::ModifyAttributeValue(float Value, EAtributeType Atribute)
{
    if (!AtributosSystem || bDied) return;
    
    float* Current = nullptr;
    
    switch (Atribute)
    {
    case EAtributeType::Vida:    Current = &Health; break;
    case EAtributeType::Mana:    Current = &Mana; break;
    case EAtributeType::Stamina: Current = &Stamina; break;
    default: return;
    }

    if (!Current) return;
    
    const float Max = GetMax(Atribute);
    
    *Current = FMath::Clamp(*Current + Value, 0.0f, Max);
    
    OnAttributeChanged.Broadcast(Atribute, *Current);

}

void UStatusComponent::HandleAttributesUpdated(UAtributosSystem* AtribComp, EAtributeType Atribute, float Amount)
{
    ModifyAttributeValue(Amount, Atribute);

    if (Health <= 0.0f && !bDied)
        ApplyDeath();
}


float UStatusComponent::GetMax(EAtributeType Type) const
{
    return AtributosSystem ? (AtributosSystem->GetValue(Type)) : 0.f;
}

void UStatusComponent::ApplyDeath()
{
    if (bDied) return;
    bDied = true;
    UE_LOG(LogTemp, Warning, TEXT("Death!"));
    OnDied.Broadcast();
}
