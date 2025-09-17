#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelWidget.generated.h"

class UProgressBar;
class UTextBlock;
class ULevelComponent;

UCLASS()
class ISEKAI_API ULevelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category="Level")
	void InitializeWidget(ULevelComponent* InLevelComponent);

protected:
	// BindWidgets no BP
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UProgressBar* XPProgressBar;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* LevelText;

private:
	UPROPERTY()
	ULevelComponent* LevelComponent;

	// Funções que reagem aos delegates
	UFUNCTION()
	void OnXPChanged(float NewXP);

	UFUNCTION()
	void OnLevelUp(int32 NewLevel);

	// Atualiza UI toda vez que algo mudar
	void UpdateXPBar();
	void UpdateLevelText();
};
