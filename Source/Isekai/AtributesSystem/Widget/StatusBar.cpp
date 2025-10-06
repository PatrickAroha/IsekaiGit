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
				StatusComponent->OnAttributeChanged.AddDynamic(this, &UStatusBar::OnAttributeUpdated);
				
				UpdateBarValue(StatusComponent->GetMax(AtributeType));
			}
		}
	}
}

void UStatusBar::OnAttributeUpdated(EAtributeType Atribute, float NewValue)
{
	if (Atribute == AtributeType)
	{
		UpdateBarValue(NewValue);
	}
}

void UStatusBar::UpdateBarValue(float NewValue)
{
	if (!StatusComponent || !ProgressBar || !TextBarValue)
		return;

	const float Max = StatusComponent->GetMax(AtributeType);
	const float Normalized = (Max > 0.f) ? (NewValue / Max) : 0.f;

	ProgressBar->SetPercent(Normalized);

	const FString Text = FString::Printf(TEXT("%.0f / %.0f"), NewValue, Max);
	TextBarValue->SetText(FText::FromString(Text));
}
