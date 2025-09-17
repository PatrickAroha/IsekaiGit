#include "LevelWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Isekai/AtributesSystem/LevelComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ULevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Procura o LevelComponent automaticamente
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (ULevelComponent* LvlComp = Pawn->FindComponentByClass<ULevelComponent>())
			{
				InitializeWidget(LvlComp);
			}
		}
	}
}

void ULevelWidget::InitializeWidget(ULevelComponent* InLevelComponent)
{
	if (!InLevelComponent) return;

	LevelComponent = InLevelComponent;

	// Bind nos delegates
	LevelComponent->OnXPChanged.AddDynamic(this, &ULevelWidget::OnXPChanged);
	LevelComponent->OnLevelUp.AddDynamic(this, &ULevelWidget::OnLevelUp);

	// Atualiza UI inicial
	OnXPChanged(LevelComponent->GetCurrentXP());
	OnLevelUp(LevelComponent->GetCurrentLevel());
}

void ULevelWidget::OnXPChanged(float NewXP)
{
	if (XPProgressBar && LevelComponent)
	{
		XPProgressBar->SetPercent(LevelComponent->GetNormalizedXP());
	}
}

void ULevelWidget::OnLevelUp(int32 NewLevel)
{
	if (LevelText)
	{
		LevelText->SetText(FText::AsNumber(NewLevel));
	}
}
