#include "Atributs.h"

#include "Isekai/AtributesSystem/LevelComponent.h"
#include "Isekai/Character/IsekaiCharacter.h"

void UAtributs::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (AIsekaiCharacter* IsekaiPlayer = Cast<AIsekaiCharacter>(Pawn))
			{
				Player = IsekaiPlayer;
				
				if (UAtributosSystem* AtribComp = Pawn->FindComponentByClass<UAtributosSystem>())
				{
					UpdateAttributes(AtribComp,  EAtributeType::Attack, 0);

					AtribComponent = AtribComp;

					if (!AtribComp->OnAttributesUpdated.IsAlreadyBound(this, &UAtributs::UpdateAttributes))
					{
						AtribComp->OnAttributesUpdated.AddDynamic(this, &UAtributs::UpdateAttributes);
					}
				}
			}
		}
	}
}

void UAtributs::UpdateAttributes(UAtributosSystem* AtribComp, EAtributeType Atribute, float Amount)
{
	if (!AtribComp) return;

	if (VidaText) 
		VidaText->SetText(FText::FromString(
			FString::Printf(TEXT("Health: %.1f"), AtribComp->Attributes[EAtributeType::Vida])
		));

	if (StaminaText) 
		StaminaText->SetText(FText::FromString(
			FString::Printf(TEXT("Stamina: %.1f"), AtribComp->Attributes[EAtributeType::Stamina])
		));

	if (ManaText) 
		ManaText->SetText(FText::FromString(
			FString::Printf(TEXT("Mana: %.1f"), AtribComp->Attributes[EAtributeType::Mana])
		));

	if (AttackText) 
		AttackText->SetText(FText::FromString(
			FString::Printf(TEXT("Attack: %.1f"), AtribComp->Attributes[EAtributeType::Attack])
		));

	if (PowerText) 
		PowerText->SetText(FText::FromString(
			FString::Printf(TEXT("Hability Power: %.1f"), AtribComp->Attributes[EAtributeType::Power])
		));

	if (DefenseText) 
		DefenseText->SetText(FText::FromString(
			FString::Printf(TEXT("Armor: %.1f"), AtribComp->Attributes[EAtributeType::Defense])
		));

	if (VelocityText) 
		VelocityText->SetText(FText::FromString(
			FString::Printf(TEXT("Velocity: %.1f"), AtribComp->Attributes[EAtributeType::Velocity])
		));

	if (JumpText) 
		JumpText->SetText(FText::FromString(
			FString::Printf(TEXT("Jump: %.1f"), AtribComp->Attributes[EAtributeType::Jump])
		));

	if (DodgeText) 
		DodgeText->SetText(FText::FromString(
			FString::Printf(TEXT("Dodge: %.1f"), AtribComp->Attributes[EAtributeType::Dodge])
		));
}

void UAtributs::UpdateAtributeLevel(EAtributeType Atribute)
{
	if (!Player || !Player->LevelComponent || !AtribComponent) return;
	
	if (Player->LevelComponent->QuantityUpgradeLevel < Player->LevelComponent->CurrentLevel)
	{
		AtribComponent->ChangeBonusValue(Atribute, 10);
		Player->LevelComponent->QuantityUpgradeLevel++;
	}
}



