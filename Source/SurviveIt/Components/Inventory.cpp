

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

bool UInventory::AddToolToInventory(AToolItem* ToolItem)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			if (InventorySlots[(Row) * InventoryColumns + Column].Item != nullptr) continue; // Checking if slot is occupied.
			if (InventoryColumns - 1 < Column + ToolItem->GetItemWidth() - 1 || InventoryRows - 1 < Row + ToolItem->GetItemHeight() - 1) continue; // Checking if Item size is not out of bonds.

			FIntPoint Position = FIntPoint(Row, Column);
			FIntPoint ItemSize = FIntPoint(ToolItem->GetItemWidth(), ToolItem->GetItemHeight());

			if (CheckSpaceAvailable(Position, ItemSize))
			{
				OccupySlots(Position, ItemSize, ToolItem);
				return true;
			}
		}
	}
	return false;
}

bool UInventory::AddResourceToInventory(AResourceItem* ResourceItem)
{
	if (!ResourceItem) return false;

	const EResourceType ResourceType = ResourceItem->GetResourceType();
	int32 RemainingQuantity = ResourceItem->GetResourceQuantity();
	const int32 MaxStack = ResourceItem->GetMaxStack();

	while (RemainingQuantity > 0)
	{
		int32 QuantityToAdd = FMath::Min(RemainingQuantity, MaxStack);
		RemainingQuantity -= QuantityToAdd;

		bool bAddedToExisting = false;

		/** Adding to Existing ResourceMap */
		if (ResourceMap.Contains(ResourceType))
		{
			for (AResourceItem* ExistingItem : ResourceMap[ResourceType].Items)
			{
				UE_LOG(LogTemp, Warning, TEXT("Amount: %i"), ExistingItem->GetResourceQuantity());
				if (ExistingItem->CanAddQuantity(QuantityToAdd))
				{
					ExistingItem->AddQuantity(QuantityToAdd);
					bAddedToExisting = true;
					break;
				}
				else 
				{
					QuantityToAdd -= (ExistingItem->GetMaxStack() - ExistingItem->GetResourceQuantity());
					ExistingItem->AddQuantity(MaxStack);
				}
			}
		}
		
		if (!bAddedToExisting) 
		{ 
			AResourceItem* NewStack = nullptr;

			if (QuantityToAdd == ResourceItem->GetResourceQuantity()) /** If first Iteration use ResourceItem */
			{
				NewStack = ResourceItem;
				NewStack->SetResourceQuantity(QuantityToAdd);
			}
			else
			{
				NewStack = NewObject<AResourceItem>(ResourceItem->GetClass());
				NewStack->Initialize(ResourceType, QuantityToAdd, MaxStack);
			}
			AddNewStack(NewStack);

			if (!ResourceMap.Contains(ResourceType))
			{
				ResourceMap.Add(ResourceType, FResourceItemArray());
			}
			ResourceMap[ResourceType].Items.Add(NewStack);
		}
	}
	ResourceItem->Destroy();
	return true;
}

bool UInventory::AddNewStack(AResourceItem* Resource)
{
	for (int Row = 0; InventoryRows > Row; Row++)
	{
		for (int Column = 0; InventoryColumns > Column; Column++)
		{
			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue; // Checking if slot is occupied.

			FIntPoint Position = FIntPoint(Row, Column);
			FIntPoint ItemSize = FIntPoint(Resource->GetItemWidth(), Resource->GetItemHeight());
			if (CheckSpaceAvailable(Position, ItemSize))
			{
				OccupySlots(Position, ItemSize, Resource);
				return true;
			}
		}
	}
	return false;
}

//bool UInventory::AddToInventory(AItemBase* Item)
//{
//	for (int Row = 0; InventoryRows > Row; Row++)
//	{
//		for (int Column = 0; InventoryColumns > Column; Column++)
//		{
//			// Conditions to Continue loop
//			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue;
//			if (InventoryColumns - 1 < Column + Item->GetItemWidth() - 1 || InventoryRows - 1 < Row + Item->GetItemHeight() - 1) continue;
//		
//			if (ItemCanFit(Row, Column, Item)) // Checking if the item will fit
//			{
//				for (int Width = 0; Item->GetItemWidth() > Width; Width++)
//				{
//					for (int Height = 0; Item->GetItemHeight() > Height; Height++)
//					{
//						InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item = Item; // Adding items to Inventory
//					}
//				}
//				if (InventoryWidget)
//				{
//					InventoryWidget->AddItemToWidget(FVector2D(Row, Column), SlotSize, Item); // Adding items to Widget inventory
//				}
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//bool UInventory::AddToInventoryWithQuantiy(AItemBase* Item)
//{
//	for (int Row = 0; InventoryRows > Row; Row++)
//	{
//		for (int Column = 0; InventoryColumns > Column; Column++)
//		{
//			if (InventorySlots[(Row)*InventoryColumns + Column].Item != nullptr) continue;
//
//			for (int Width = 0; Item->GetItemWidth() > Width; Width++)
//			{
//				for (int Height = 0; Item->GetItemHeight() > Height; Height++)
//				{
//					InventorySlots[(Row + Height) * InventoryColumns + Column + Width].Item = Item; // Adding items to Inventory
//				}
//			}
//			if (InventoryWidget)
//			{
//				InventoryWidget->AddItemToWidget(FVector2D(Row, Column), SlotSize, Item); // Adding items to Widget inventory
//			}
//			return true;
//		}
//	}
//	return false;
//}

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
