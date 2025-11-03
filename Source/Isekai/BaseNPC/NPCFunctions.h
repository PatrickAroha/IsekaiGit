// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NPCFunctions.generated.h"

class AIsekaiCharacter;
class ABaseNPC;

UCLASS(Blueprintable, BlueprintType)
class ISEKAI_API UNPCFunctions : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AIsekaiCharacter* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseNPC* CallerRef;
	
public:
	void StartFunction(AIsekaiCharacter* Player, ABaseNPC* Caller);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ExecuteFunction();

	UFUNCTION(BlueprintCallable)
	void EndExecute();

	virtual UWorld* GetWorld() const override;
};
