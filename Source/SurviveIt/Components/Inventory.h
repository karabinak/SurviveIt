
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurviveIt/Data/ItemData.h"
#include "Inventory.generated.h"


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


public:	

	bool AddToInventory(int32 Width, int32 Height, AItemBase* Item);

		
};
