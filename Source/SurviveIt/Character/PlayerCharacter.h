#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventory;
class AItemBase;
class AToolItem;
class UPlayerWidget;
//class UInventoryWidget;

UCLASS()
class SURVIVEIT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	void OnInteractionTriggered();

	bool IsInventoryVisible();

	void OnLMBClicked();

	void TraceLine();

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float InteractionLength = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* HitActor = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	bool bToolEquipped = false;

	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	AToolItem* EquippedTool = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UPlayerWidget* PlayerWidget;


public:	

	FORCEINLINE bool GetToolEquipped() { return bToolEquipped; }

};
