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
	}
}

void ASurvivalController::OnMoveTriggered(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		PlayerCharacter->AddMovementInput(FVector(MoveValue.X, MoveValue.Y, 0.f));
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

}