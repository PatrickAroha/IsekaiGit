#include "Atributs.h"

void UAtributs::UpdateAttributes(UAtributosSystem* AtribComp, EAtributeType Atribute, float Amount)
{
	if (!AtribComp) return;

	if (VidaText) 
		VidaText->SetText(FText::FromString(
			FString::Printf(TEXT("Health: %d"), AtribComp->Attributes[EAtributeType::Vida])
		));

	if (StaminaText) 
		StaminaText->SetText(FText::FromString(
			FString::Printf(TEXT("Stamina: %d"), AtribComp->Attributes[EAtributeType::Stamina])
		));

	if (ManaText) 
		ManaText->SetText(FText::FromString(
			FString::Printf(TEXT("Mana: %d"), AtribComp->Attributes[EAtributeType::Mana])
		));

	if (AttackText) 
		AttackText->SetText(FText::FromString(
			FString::Printf(TEXT("Attack: %d"), AtribComp->Attributes[EAtributeType::Attack])
		));

	if (PowerText) 
		PowerText->SetText(FText::FromString(
			FString::Printf(TEXT("Hability Power: %d"), AtribComp->Attributes[EAtributeType::Power])
		));

	if (DefenseText) 
		DefenseText->SetText(FText::FromString(
			FString::Printf(TEXT("Armor: %d"), AtribComp->Attributes[EAtributeType::Defense])
		));

	if (VelocityText) 
		VelocityText->SetText(FText::FromString(
			FString::Printf(TEXT("Velocity: %d"), AtribComp->Attributes[EAtributeType::Velocity])
		));

	if (JumpText) 
		JumpText->SetText(FText::FromString(
			FString::Printf(TEXT("Jump: %d"), AtribComp->Attributes[EAtributeType::Jump])
		));

	if (DodgeText) 
		DodgeText->SetText(FText::FromString(
			FString::Printf(TEXT("Dodge: %d"), AtribComp->Attributes[EAtributeType::Dodge])
		));
}

void UAtributs::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (UAtributosSystem* AtribComp = Pawn->FindComponentByClass<UAtributosSystem>())
			{
				UpdateAttributes(AtribComp,  EAtributeType::Attack, 0);

				AtribComp->OnAttributesUpdated.AddDynamic(this, &UAtributs::UpdateAttributes);
			}
		}
	}
}

