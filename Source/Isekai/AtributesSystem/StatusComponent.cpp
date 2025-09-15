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

            Health  = GetMax(EAtributeType::Vida);
            Stamina = GetMax(EAtributeType::Stamina);
            Mana    = GetMax(EAtributeType::Mana);

   
            AtributosSystem->OnAttributesUpdated.AddDynamic(this, &UStatusComponent::HandleAttributesUpdated);
        }
    }
}

float UStatusComponent::GetMax(EAtributeType Type) const
{
    return AtributosSystem ? static_cast<float>(AtributosSystem->GetValue(Type)) : 0.f;
}

void UStatusComponent::ApplyDeath()
{
    if (bDied) return;    
    bDied = true;
    OnDied.Broadcast();        
}

// ---------- HEALTH ----------
void UStatusComponent::SubtractHealth(float Value)
{
    if (!AtributosSystem || bDied) return;

    const float Old = Health;
    Health = FMath::Max(Health - Value, 0.0f);
    OnHealthChanged.Broadcast(Old, Health);
    
    if (Health <= 0.0f)
    {
        ApplyDeath();
    }
}

void UStatusComponent::AddHealth(float Value)
{
    if (!AtributosSystem || bDied) return;

    const float Old = Health;
    Health = FMath::Clamp(Health + Value, 0.0f, GetMax(EAtributeType::Vida));
    OnHealthChanged.Broadcast(Old, Health);
}

// ---------- STAMINA ----------
void UStatusComponent::SubtractStamina(float Value)
{
    if (!AtributosSystem) return;

    const float Old = Stamina;
    Stamina = FMath::Max(Stamina - Value, 0.0f);
    OnStaminaChanged.Broadcast(Old, Stamina);
    
}

void UStatusComponent::AddStamina(float Value)
{
    if (!AtributosSystem) return;

    const float Old = Stamina;
    Stamina = FMath::Clamp(Stamina + Value, 0.0f, GetMax(EAtributeType::Stamina));
    OnStaminaChanged.Broadcast(Old, Stamina);
    
}

// ---------- MANA ----------
void UStatusComponent::SubtractMana(float Value)
{
    if (!AtributosSystem) return;

    const float Old = Mana;
    Mana = FMath::Max(Mana - Value, 0.0f);
    OnManaChanged.Broadcast(Old, Mana);
}

void UStatusComponent::AddMana(float Value)
{
    if (!AtributosSystem) return;

    const float Old = Mana;
    Mana = FMath::Clamp(Mana + Value, 0.0f, GetMax(EAtributeType::Mana));
    OnManaChanged.Broadcast(Old, Mana);
}

// ---------- UTIL ----------
float UStatusComponent::GetNormalizedHealth() const
{
    const float MaxH = GetMax(EAtributeType::Vida);
    return (MaxH > 0.f) ? (Health / MaxH) : 0.0f;
}

void UStatusComponent::HandleAttributesUpdated(UAtributosSystem* /*AtribComp*/)
{
    Health  = FMath::Clamp(Health,  0.0f, GetMax(EAtributeType::Vida));
    Stamina = FMath::Clamp(Stamina, 0.0f, GetMax(EAtributeType::Stamina));
    Mana    = FMath::Clamp(Mana,    0.0f, GetMax(EAtributeType::Mana));
    
    OnHealthChanged.Broadcast(Health, Health);
    OnStaminaChanged.Broadcast(Stamina, Stamina);
    OnManaChanged.Broadcast(Mana, Mana);
    
    if (Health <= 0.0f && !bDied)
    {
        ApplyDeath();
    }
}