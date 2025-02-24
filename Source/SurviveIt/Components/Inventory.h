
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurviveIt/Data/InventoryData.h"
#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "Inventory.generated.h"

class UInventoryWidget;
class AToolItem;
class AResourceItem;
class AItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UInventory : public UActorComponent, public IInventoryHandler
{
	GENERATED_BODY()

public:	
	UInventory();

	bool AddToolToInventory(AToolItem* Tool);
	bool AddResourceToInventory(AResourceItem* Resource);

	bool AddNewStack(AResourceItem* Resource);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	bool CheckSpaceAvailable(const FIntPoint& Position, const FIntPoint& ItemSize);
	UFUNCTION()
	void OccupySlots(const FIntPoint& Position, const FIntPoint& ItemSize, AItemBase* Item);
	UFUNCTION()
	void FreeSlots(AItemBase* Item);

private:

	UPROPERTY(EditAnywhere)
	TArray<FInventorySlot> InventorySlots;

	UPROPERTY()
	TMap<EResourceType, FResourceItemArray> ResourceMap;

	UPROPERTY(EditAnywhere)
	int32 InventoryColumns = 15;

	UPROPERTY(EditAnywhere)
	int32 InventoryRows = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	float SlotSize = 80.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	bool bInvnetoryVisible = false;


public:	

	//bool AddToInventory(AItemBase* Item);
	//bool AddToInventoryWithQuantiy(AItemBase* Item);

	bool ItemCanFit(int32 Row, int32 Column, AItemBase* Item);

	bool IsInventoryWidgetVisible();

};


