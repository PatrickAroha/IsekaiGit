#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Isekai/AtributesSystem/AtributosSystem.h"
#include "Atributs.generated.h"

UCLASS()
class ISEKAI_API UAtributs : public UUserWidget
{
	GENERATED_BODY()

public:     
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* VidaText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StaminaText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ManaText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AttackText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PowerText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DefenseText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* VelocityText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* JumpText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DodgeText;

	UFUNCTION()
	void UpdateAttributes(UAtributosSystem* AtribComp, EAtributeType Atribute, float Amount);

	virtual void NativeConstruct() override;
	
};
