#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

// Delegates para notificação
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXPChanged, float, NewXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULevelComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	int32 CurrentLevel = 1;
protected:
	virtual void BeginPlay() override;

	// ========= PROPRIEDADES =========

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float CurrentXP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float XPToNextLevel = 100.0f; // XP inicial necessária

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float BaseXP = 100.0f; // XP base para a fórmula

	
public:
	// ========= FUNÇÕES =========

	UFUNCTION(BlueprintCallable, Category="Level")
	void AddXP(float Amount);

	UFUNCTION(BlueprintCallable, Category="Level")
	int32 GetCurrentLevel() const { return CurrentLevel; }

	UFUNCTION(BlueprintCallable, Category="Level")
	float GetCurrentXP() const { return CurrentXP; }

	UFUNCTION(BlueprintCallable, Category="Level")
	float GetXPToNextLevel() const { return XPToNextLevel; }

	UFUNCTION(BlueprintCallable, Category="Level")
	float GetNormalizedXP() const { return (XPToNextLevel > 0) ? (CurrentXP / XPToNextLevel) : 0.0f; }

	// ========= DELEGATES =========

	// HUD pode ouvir isso pra atualizar barra de XP
	UPROPERTY(BlueprintAssignable, Category="Level")
	FOnXPChanged OnXPChanged;

	// Status/SkillTree podem ouvir isso pra reagir ao level up
	UPROPERTY(BlueprintAssignable, Category="Level")
	FOnLevelUp OnLevelUp;

	UPROPERTY(BlueprintReadWrite)
	int32 QuantityUpgradeLevel = 1;
	
private:
	void LevelUp();
	float CalculateNextXPRequirement() const;
};
