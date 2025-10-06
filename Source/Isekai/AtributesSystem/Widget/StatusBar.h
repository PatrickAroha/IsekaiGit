#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/AtributesSystem/AttributesTypes.h"
#include "StatusBar.generated.h"

class UProgressBar;
class UTextBlock;
class UStatusComponent;

UCLASS()
class ISEKAI_API UStatusBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnAttributeUpdated(EAtributeType Atribute, float NewValue);

protected:

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UProgressBar* ProgressBar;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* TextBarValue;
	
	UPROPERTY()
	UStatusComponent* StatusComponent;

	// Tipo de atributo (definido em cada BP da barra)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	EAtributeType AtributeType;

	// Atualiza visualmente a barra e o texto
	UFUNCTION()
	void UpdateBarValue(float NewValue);
};
