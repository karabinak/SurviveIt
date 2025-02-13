

#include "Inventory.h"

#include "SurviveIt/Items/ItemBase.h"
#include "SurviveIt/Widgets/InventoryWidget.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
	
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			FInventorySlot Slot;
			Slot.Row = Row;
			Slot.Column = Column;
			Slot.Item = nullptr;
			InventorySlots.Add(Slot);
		}
	}

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->InitializeGrid(SlotSize, InventoryRows, InventoryColumns);
		InventoryWidget->AddToViewport();
	}
}

bool UInventory::AddToInventory(AItemBase* Item)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue;
			if (InventoryColumns - 1 < Column + Item->GetItemWidth() - 1 || InventoryRows - 1 < Row + Item->GetItemHeight() - 1) continue;
			
			if (ItemCanFit(Row, Column, Item))
			{
				for (int Width = 0; Item->GetItemWidth() > Width; Width++)
				{
					for (int Height = 0; Item->GetItemHeight() > Height; Height++)
					{
						InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item = Item;
					}
				}
				if (InventoryWidget)
				{
					UE_LOG(LogTemp, Warning, TEXT("R %i, C %i"), Row, Column);
					FVector2D FirstTile = FVector2D(Row, Column);
					InventoryWidget->AddItemToWidget(FirstTile, SlotSize, Item);
				}
				return true;
			}
		}
	}
	return false;
}

bool UInventory::ItemCanFit(int32 Row, int32 Column, AItemBase* Item)
{
	for (int Width = 0; Item->GetItemWidth() > Width; Width++)
	{
		for (int Height = 0; Item->GetItemHeight() > Height; Height++)
		{
			if (InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item != nullptr)
			{
				return false;	
			}
		}
	}
	return true;
}


