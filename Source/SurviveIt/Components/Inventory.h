
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurviveIt/Data/ItemData.h"
#include "Inventory.generated.h"

class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();


protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TArray<FInventorySlot> InventorySlots;

	UPROPERTY(EditAnywhere)
	int32 InventoryColumns = 15;

	UPROPERTY(EditAnywhere)
	int32 InventoryRows = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	float SlotSize = 60.f;


public:	

	bool AddToInventory(AItemBase* Item);

	bool ItemCanFit(int32 Row, int32 Column, AItemBase* Item);

		
};
