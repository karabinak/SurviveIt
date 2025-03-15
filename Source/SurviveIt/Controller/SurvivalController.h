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

	UFUNCTION()
	void OnMoveTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void OnJumpTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void OnLookAroundTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void OnInteractTriggered(const FInputActionValue& Value); // NOW: Picking up items
	UFUNCTION()
	void OnToggleInventory(const FInputActionValue& Value);
	UFUNCTION()
	void OnUsePressed(const FInputActionValue& Value);
	UFUNCTION()
	void OnNumberTriggered(const FInputActionValue& Value);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAroundInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Use;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* HotbarSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* HotbarSlot2;

	UPROPERTY()
	bool bIsInventoryOpen = false;

public:
	
};
