// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Isekai/TableBase/TableBase.h"
#include "FurnaceTable.generated.h"

UCLASS()
class ISEKAI_API AFurnaceTable : public ATableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFurnaceTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
