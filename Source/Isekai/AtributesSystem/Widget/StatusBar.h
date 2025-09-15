#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/AtributesSystem/AttributesTypes.h"
#include "StatusBar.generated.h"

enum class EAtributeType : uint8;
class UProgressBar;
class UTextBlock;
class UStatusComponent;

UCLASS()
class ISEKAI_API UStatusBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UProgressBar* ProgressBar;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* TextBarValue;
	
	UPROPERTY()
	UStatusComponent* StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	EAtributeType AtributeType;
	
	UFUNCTION()
	void UpdateBarValue(float OldValue, float NewValue);
};