

#include "Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; InventoryRows > i; i++)
	{
		for (int j = 0; InventoryColumns > j; j++)
		{
			FInventorySlot Slot;
			Slot.Row = i;
			Slot.Column = j;
			Slot.Item = nullptr;
			InventorySlots.Add(Slot);
		}
	}
}

bool UInventory::AddToInventory(int32 Width, int32 Height, AItemBase* Item)
{
	

	return false;
}


