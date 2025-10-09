// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Isekai/Interfaces/InteractInterface.h"
#include "TableBase.generated.h"

UCLASS()
class ISEKAI_API ATableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:

	ATableBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Craft|Mesh")
	UStaticMeshComponent* TableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft|UI")
	TSubclassOf<UUserWidget> WidgetClass;

	virtual void Interact_Implementation(AIsekaiCharacter* Player) override;
	virtual void BeginFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;

protected:

	virtual void BeginPlay() override;
	
};
