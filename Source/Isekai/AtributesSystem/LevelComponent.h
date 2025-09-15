#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

// Delegates para notificação
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXPChanged, float, NewXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULevelComponent();

protected:
	virtual void BeginPlay() override;

	// ========= PROPRIEDADES =========

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	int32 CurrentLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float CurrentXP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float XPToNextLevel = 100.0f; // XP inicial necessária

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level")
	float XPScale = 1.25f; // multiplicador de dificuldade (progressão)

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

	// ========= DELEGATES =========

	// HUD pode ouvir isso pra atualizar barra de XP
	UPROPERTY(BlueprintAssignable, Category="Level")
	FOnXPChanged OnXPChanged;

	// Status/SkillTree podem ouvir isso pra reagir ao level up
	UPROPERTY(BlueprintAssignable, Category="Level")
	FOnLevelUp OnLevelUp;

private:
	void LevelUp();
	float CalculateNextXPRequirement() const;
};