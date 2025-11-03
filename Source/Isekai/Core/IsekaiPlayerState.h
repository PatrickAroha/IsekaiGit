#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "IsekaiPlayerState.generated.h"

UCLASS()
class ISEKAI_API AIsekaiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="Score")
	void SetPlayerScore(float NewScore)
	{
		SetScore(NewScore);
	}
	
	UFUNCTION(BlueprintPure, Category="Score")
	float GetPlayerScore() const
	{
		return GetScore();
	}

};