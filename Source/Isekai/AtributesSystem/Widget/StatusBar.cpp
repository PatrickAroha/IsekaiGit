#include "StatusBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Isekai/AtributesSystem/StatusComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void UStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			StatusComponent = Pawn->FindComponentByClass<UStatusComponent>();
			if (StatusComponent)
			{
				switch (AtributeType)
				{
				case EAtributeType::Vida:
					StatusComponent->OnHealthChanged.AddDynamic(this, &UStatusBar::UpdateBarValue);
					UpdateBarValue(StatusComponent->Health, StatusComponent->Health);
					break;

				case EAtributeType::Mana:
					StatusComponent->OnManaChanged.AddDynamic(this, &UStatusBar::UpdateBarValue);
					UpdateBarValue(StatusComponent->Mana, StatusComponent->Mana);
					break;

				case EAtributeType::Stamina:
					StatusComponent->OnStaminaChanged.AddDynamic(this, &UStatusBar::UpdateBarValue);
					UpdateBarValue(StatusComponent->Stamina, StatusComponent->Stamina);
					break;

				default: ;
					
				}
			}
		}
	}
}

void UStatusBar::UpdateBarValue(float OldValue, float NewValue)
{
	if (!StatusComponent || !ProgressBar || !TextBarValue)
		return;

	const float Max = StatusComponent->GetMax(AtributeType);
	const float Normalized = (Max > 0.f) ? (NewValue / Max) : 0.f;

	ProgressBar->SetPercent(Normalized);

	FString Text = FString::Printf(TEXT("%.1f / %.1f"), NewValue, Max);
	TextBarValue->SetText(FText::FromString(Text));
}