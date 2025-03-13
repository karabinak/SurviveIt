#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInventoryComponent;
class UHotbarComponent;
class UBaseItem;
class UToolItem;

//class UInventoryWidget;

UCLASS()
class SURVIVEIT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHotbarComponent* HotbarComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float InteractionDistance;

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

public:

	virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UHotbarComponent* GetHotbarComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryPickupItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool DropItemFromInventory(UBaseItem* Item, int32 Quantity = 1);

	void UseHotbarItem();

	void SelectHotbarSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* GetLookAtActor(float MaxDistance = 800.f);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool TryHarvest();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	UToolItem* GetEquippedTool();

};
