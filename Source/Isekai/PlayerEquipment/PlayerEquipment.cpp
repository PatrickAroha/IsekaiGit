// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEquipment.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerEquipment::APlayerEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
void APlayerEquipment::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
*/
