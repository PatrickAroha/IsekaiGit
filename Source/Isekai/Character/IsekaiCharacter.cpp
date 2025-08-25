// Copyright Epic Games, Inc. All Rights Reserved.

#include "IsekaiCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "isekai/Inventory/InventoryComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "VectorUtil.h"
#include "Blueprint/UserWidget.h"
#include "Isekai/Inventory/PDA_Master.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AIsekaiCharacter::AIsekaiCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
	
}


void AIsekaiCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AIsekaiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIsekaiCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIsekaiCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AIsekaiCharacter::Interact);

		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AIsekaiCharacter::OpenInventory);

		EnhancedInputComponent->BindAction(InventoryClear, ETriggerEvent::Started, this, &AIsekaiCharacter::ClearInventory);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AIsekaiCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AIsekaiCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AIsekaiCharacter::Linetrace()
{
	UCameraComponent* Camera = GetFollowCamera();
	if (!Camera) return;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start+ (Camera->GetForwardVector() * 1000.0f);
		
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECC_Visibility,TraceParams))
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.2f);
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			if (CurrentTarget == nullptr)
			{
				CurrentTarget = HitResult.GetActor();
				TargetInteractable->Execute_BeginFocus(CurrentTarget);
				return;
			}

			if (HitResult.GetActor() == CurrentTarget)
			{
				return;
			}
			
			if (HitResult.GetActor() != CurrentTarget)
			{
				TargetInteractable->Execute_EndFocus(CurrentTarget);
				CurrentTarget = HitResult.GetActor();
				TargetInteractable->Execute_BeginFocus(CurrentTarget);
				return;
			}
		}
	}
	if (CurrentTarget)
	TargetInteractable->Execute_EndFocus(CurrentTarget);

	CurrentTarget = nullptr;
}


void AIsekaiCharacter::Interact()
{
	if (CurrentTarget != nullptr)
	{
		TargetInteractable->Execute_Interact(CurrentTarget, this);
		if (Inventory)
			Inventory->InitItems(InventoryComponent->ItemSlots);
	}
}

void AIsekaiCharacter::OpenInventory()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{

		if (InventoryClass == nullptr) return;
		
		if (Inventory)
		{
			FInputModeGameOnly InputMode;
			Inventory->RemoveFromParent();
			Inventory = nullptr;
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = false;
		}
		else
		{
	
			if (InventoryComponent)
			{
				Inventory = CreateWidget<UBaseInventory>(GetWorld(), InventoryClass);
				Inventory->InitItems(InventoryComponent->ItemSlots);
				
				FInputModeGameAndUI InputMode;
				Inventory->SetFocus();
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				
				PC->SetInputMode(InputMode);
				PC->bShowMouseCursor = true;
			}

				Inventory->AddToViewport();
		}
	}
	
}

void AIsekaiCharacter::ClearInventory()
{
	if (InventoryComponent) InventoryComponent->ClearInventory();
}

void AIsekaiCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Linetrace();
}