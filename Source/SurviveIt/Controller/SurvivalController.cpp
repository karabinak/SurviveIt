#include "SurvivalController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "SurviveIt/Character/PlayerCharacter.h"

ASurvivalController::ASurvivalController()
{

}

void ASurvivalController::BeginPlay()
{
	Super::BeginPlay();
}

void ASurvivalController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ThisClass::OnMoveTriggered);
		EnhancedInputComponent->BindAction(LookAroundInput, ETriggerEvent::Triggered, this, &ThisClass::OnLookAroundTriggered);
		EnhancedInputComponent->BindAction(JumpInput, ETriggerEvent::Started, this, &ThisClass::OnJumpTriggered);
		EnhancedInputComponent->BindAction(Interact, ETriggerEvent::Started, this, &ThisClass::OnInteractTriggered);
		EnhancedInputComponent->BindAction(Inventory, ETriggerEvent::Started, this, &ThisClass::OnInventoryTriggered);
	}
}

void ASurvivalController::OnMoveTriggered(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();

		const FRotator YawRotationX(0.f, GetControlRotation().Yaw, 0.f);
		const FVector DirectionX(FRotationMatrix(YawRotationX).GetUnitAxis(EAxis::X));
		PlayerCharacter->AddMovementInput(DirectionX, MoveValue.X);

		const FRotator YawRotationY(0.f, GetControlRotation().Yaw, 0.f);
		const FVector DirectionY(FRotationMatrix(YawRotationY).GetUnitAxis(EAxis::Y));
		PlayerCharacter->AddMovementInput(DirectionY, MoveValue.Y);
	}
}

void ASurvivalController::OnLookAroundTriggered(const FInputActionValue& Value)
{
	FVector2D LookValue = Value.Get<FVector2D>();

	AddYawInput(LookValue.X);
	AddPitchInput(LookValue.Y);
}

void ASurvivalController::OnJumpTriggered(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->Jump();
	}
}

void ASurvivalController::OnInteractTriggered(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnInteractionTriggered();
	}
}

void ASurvivalController::OnInventoryTriggered(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnInventoryTriggered();
	}
}
