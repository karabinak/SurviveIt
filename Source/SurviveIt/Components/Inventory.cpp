

#include "Inventory.h"

//#include "SurviveIt/Items/ItemBase.h"
#include "SurviveIt/Items/ToolItem.h"
#include "SurviveIt/Items/ResourceItem.h"
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
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryWidget->AddToViewport();
	}
}

bool UInventory::AddToolToInventory(AToolItem* Tool)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			if (InventorySlots[(Row) * InventoryColumns + Column].Item != nullptr) continue; // Checking if slot is occupied.
			if (InventoryColumns - 1 < Column + Tool->GetItemWidth() - 1 || InventoryRows - 1 < Row + Tool->GetItemHeight() - 1) continue; // Checking if Item size is not out of bonds.

			FIntPoint Position = FIntPoint(Row, Column);
			FIntPoint ItemSize = FIntPoint(Tool->GetItemWidth(), Tool->GetItemHeight());
			if (CheckSpaceAvailable(Position, ItemSize))
			{
				OccupySlots(Position, ItemSize, Tool);
				return true;
			}
		}
	}
	return false;
}

bool UInventory::AddResourceToInventory(AResourceItem* Resource)
{
	if (ResourceMap.Contains(Resource->GetResourceType()))
	{
		for (AResourceItem* ExistingItem : ResourceMap[Resource->GetResourceType()].Items)
		{
			if (ExistingItem->CanAddQuantity(Resource->GetResourceQuantity())) 
			{
				if(int32 Quantity = ExistingItem->AddQuantity(Resource->GetResourceQuantity())) // If 0 false
				{
					UE_LOG(LogTemp, Warning, TEXT("Reszta: %i"), Quantity);
					ResourceMap[Resource->GetResourceType()].Items.Add(Resource);
					continue;
				}
				else
				{
					return true;
				}
			}
		}
	}
	else
	{
		// ------------------------------------------------------------------

		for (int Row = 0; InventoryRows > Row; Row++)
		{
			for (int Column = 0; InventoryColumns > Column; Column++)
			{
				if (InventorySlots[(Row) * InventoryColumns + Column].Item != nullptr) continue; // Checking if slot is occupied.

				FIntPoint Position = FIntPoint(Row, Column);
				FIntPoint ItemSize = FIntPoint(Resource->GetItemWidth(), Resource->GetItemHeight());
				if (CheckSpaceAvailable(Position, ItemSize))
				{
					ResourceMap.Add(Resource->GetResourceType(), FResourceItemArray());
					ResourceMap[Resource->GetResourceType()].Items.Add(Resource);
					OccupySlots(Position, ItemSize, Resource);
					return true;
				}
			}
		}
	}
	return false;
}

bool UInventory::AddToInventory(AItemBase* Item)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			// Conditions to Continue loop
			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue;
			if (InventoryColumns - 1 < Column + Item->GetItemWidth() - 1 || InventoryRows - 1 < Row + Item->GetItemHeight() - 1) continue;
		
			if (ItemCanFit(Row, Column, Item)) // Checking if the item will fit
			{
				for (int Width = 0; Item->GetItemWidth() > Width; Width++)
				{
					for (int Height = 0; Item->GetItemHeight() > Height; Height++)
					{
						InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item = Item; // Adding items to Inventory
					}
				}
				if (InventoryWidget)
				{
					InventoryWidget->AddItemToWidget(FVector2D(Row, Column), SlotSize, Item); // Adding items to Widget inventory
				}
				return true;
			}
		}
	}
	return false;
}

bool UInventory::AddToInventoryWithQuantiy(AItemBase* Item)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue;

			for (int Width = 0; Item->GetItemWidth() > Width; Width++)
			{
				for (int Height = 0; Item->GetItemHeight() > Height; Height++)
				{
					InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item = Item; // Adding items to Inventory
				}
			}
			if (InventoryWidget)
			{
				InventoryWidget->AddItemToWidget(FVector2D(Row, Column), SlotSize, Item); // Adding items to Widget inventory
			}
			return true;
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

bool UInventory::IsInventoryWidgetVisible()
{
	if (!InventoryWidget) return false;
	if (bInvnetoryVisible)
	{
		bInvnetoryVisible = false;
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		return false;
	}
	else
	{
		bInvnetoryVisible = true;
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		return true;
	}
}

bool UInventory::CheckSpaceAvailable(const FIntPoint& Position, const FIntPoint& ItemSize)
{
	for (int Width = 0; ItemSize.X > Width; Width++)
	{
		for (int Height = 0; ItemSize.Y > Height; Height++)
		{
			if (InventorySlots[(Position.X + Height) * InventoryColumns + Position.Y + Width].Item != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void UInventory::OccupySlots(const FIntPoint& Position, const FIntPoint& ItemSize, AItemBase* Item)
{
	for (int Width = 0; Item->GetItemWidth() > Width; Width++)
	{
		for (int Height = 0; Item->GetItemHeight() > Height; Height++)
		{
			InventorySlots[(Position.X + Height) * InventoryColumns + Position.Y + Width].Item = Item; // Adding items to Inventory
		}
	}
	if (InventoryWidget)
	{
		InventoryWidget->AddItemToWidget(FVector2D(Position.X, Position.Y), SlotSize, Item); // Adding items to Widget inventory
	}
}

void UInventory::FreeSlots(AItemBase* Item)
{
}
