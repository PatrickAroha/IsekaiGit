// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTableCraft.generated.h"

UCLASS()
class ISEKAI_API ABaseTableCraft : public AActor
{
	GENERATED_BODY()

public:

	ABaseTableCraft();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
