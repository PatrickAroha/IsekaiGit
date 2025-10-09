// Fill out your copyright notice in the Description page of Project Settings.


#include "TableBase.h"

ATableBase::ATableBase(): TableMesh(nullptr)
{
	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	RootComponent = TableMesh;
}

void ATableBase::Interact_Implementation(AIsekaiCharacter* Player)
{
	
}

void ATableBase::BeginFocus_Implementation()
{
	IInteractInterface::BeginFocus_Implementation();

	if (TableMesh)
	{
		TableMesh->SetRenderCustomDepth(true);
	}
}

void ATableBase::EndFocus_Implementation()
{
	if (TableMesh)
	{
		TableMesh->SetRenderCustomDepth(false);
	}
}

void ATableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

