#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SurvivalController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SURVIVEIT_API ASurvivalController : public APlayerController
{
	GENERATED_BODY()

public:

	ASurvivalController();



protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnMoveTriggered(const FInputActionValue& Value);
	void OnJumpTriggered(const FInputActionValue& Value);
	void OnLookAroundTriggered(const FInputActionValue& Value);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAroundInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpInput;

public:
	
};
