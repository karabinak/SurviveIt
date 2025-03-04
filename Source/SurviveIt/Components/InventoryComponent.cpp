

#include "InventoryComponent.h"

#include "SurviveIt/Items/BaseItem.h"
//#include "SurviveIt/Items/ToolItem.h"
//#include "SurviveIt/Items/ResourceItem.h"
#include "SurviveIt/Widgets/InventoryWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InventoryWidth = 5; // X
	InventoryHeight = 10; // Y
}

void UInventoryComponent::Initialize(int32 Width, int32 Height)
{
	InventoryWidth = FMath::Max(1, Width);
	InventoryHeight = FMath::Max(1, Height);

	InitializeGrid();
}

bool UInventoryComponent::IsValidPosition(int32 X, int32 Y) const
{
	return X >= 0 && X < InventoryWidth && Y >= 0 && Y < InventoryHeight;
}

bool UInventoryComponent::CanItemFitAt(UBaseItem* Item, int32 X, int32 Y) const
{
	if (!Item && !Item->GetItemData()) return false;

	int32 ItemWidth = Item->GetItemData()->Width;
	int32 ItemHeight = Item->GetItemData()->Height;

	if (X < 0 || Y < 0 || X + ItemWidth > InventoryWidth || Y + ItemHeight > InventoryHeight) return false;

	return AreItemSlotsEmpty(Item, X, Y);
}

bool UInventoryComponent::AddItemAt(UBaseItem* Item, int32 X, int32 Y)
{
	if (!Item || Item->IsEmpty() || !CanItemFitAt(Item, X, Y)) return false;

	SetItemSlots(Item, X, Y);
	OnInventoryChanged.Broadcast();

	return true;
}

bool UInventoryComponent::AddItem(UBaseItem* Item)
{
	if (!Item || Item->IsEmpty()) return false;
	if (TryStackItem(Item) && Item->IsEmpty()) return true;

	// If we couldn't stack or there's still quantity left, find a position
	int32 FoundX = 0;
	int32 FoundY = 0;

	if (FindFirstFitPosition(Item, FoundX, FoundY))
	{
		return AddItemAt(Item, FoundX, FoundY);
	}

	return false;
}

bool UInventoryComponent::TryStackItem(UBaseItem* Item)
{
	if (!Item && !Item->GetItemData()) return false;

	TArray<UBaseItem*> ExistingItems = GetAllItems();
	for (UBaseItem* ExistingItem : ExistingItems)
	{
		if (Item->CanStackWith(ExistingItem))
		{
			int32 TransferredAmount = ExistingItem->TryStackWith(Item);
			OnInventoryChanged.Broadcast();

			if (Item->IsEmpty())
			{
				return true;
			}
		}
	}

	return Item->IsEmpty();
}

UBaseItem* UInventoryComponent::RemoveItemAt(int32 X, int32 Y)
{
	if (!IsValidPosition(X, Y)) return nullptr;

	UBaseItem* Item = GetItemAt(X, Y);
	if (Item)
	{
		ClearItemSlots(Item);

		OnInventoryChanged.Broadcast();
	}

	return Item;
}

UBaseItem* UInventoryComponent::GetItemAt(int32 X, int32 Y) const
{
	if (!IsValidPosition(X, Y)) return nullptr;

	int32 Index = GetSlotIndex(X, Y);
	return InventorySlots[Index].Item;
}

bool UInventoryComponent::MoveItem(int32 FromX, int32 FromY, int32 ToX, int32 ToY)
{
	UBaseItem* Item = GetItemAt(FromX, FromY);
	if (!Item) return false;

	ClearItemSlots(Item);

	if (!CanItemFitAt(Item, ToX, ToY))
	{
		SetItemSlots(Item, FromX, FromY);
		return false;
	}

	SetItemSlots(Item, ToX, ToY);
	OnInventoryChanged.Broadcast();

	return true;
}

TArray<UBaseItem*> UInventoryComponent::GetAllItems() const
{
	TArray<UBaseItem*> Result;
	TSet<UBaseItem*> UniqueItems;

	for (const FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Item && !UniqueItems.Contains(Slot.Item))
		{
			Result.Add(Slot.Item);
			UniqueItems.Add(Slot.Item);
		}
	}

	return Result;
}

TArray<FInventorySlot> UInventoryComponent::GetItemSlots(UBaseItem* Item) const
{
	TArray<FInventorySlot> Result;

	if (!Item) return Result;

	for (const FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Item == Item)
		{
			Result.Add(Slot);
		}
	}

	return Result;
}

void UInventoryComponent::ClearInventory()
{
	for (FInventorySlot& Slot : InventorySlots)
	{
		Slot.Item = nullptr;
	}

	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeGrid();
}

void UInventoryComponent::InitializeGrid()
{
	InventorySlots.Empty();
	InventorySlots.SetNum(InventoryWidth * InventoryHeight);

	for (int32 Y = 0; Y < InventoryHeight; Y++)
	{
		for (int32 X = 0; X < InventoryWidth; X++)
		{
			int32 Index = GetSlotIndex(X, Y);
			InventorySlots[Index] = FInventorySlot(X, Y);
		}
	}

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->InitializeWidget(this);
		InventoryWidget->ToggleInventory();
		InventoryWidget->AddToViewport();
	}
}

bool UInventoryComponent::AreItemSlotsEmpty(UBaseItem* Item, int32 StartX, int32 StartY) const
{
	// Checked in CanItemFitAt
	// if (!Item && !Item->GetItemData()) return false;

	int32 ItemWidth = Item->GetItemData()->Width;
	int32 ItemHeight = Item->GetItemData()->Height;

	for (int32 Y = 0; Y < ItemHeight; Y++)
	{
		for (int32 X = 0; X < ItemWidth; X++)
		{
			if (!IsValidPosition(X, Y) || GetItemAt(X, Y) != nullptr)
			{
				return false;
			}
		}
	}

	return true;
}

int32 UInventoryComponent::GetSlotIndex(int32 X, int32 Y) const
{
	return Y * InventoryWidth + X;
}

void UInventoryComponent::SetItemSlots(UBaseItem* Item, int32 StartX, int32 StartY)
{
	if (!Item || !Item->GetItemData()) return;

	int32 ItemWidth = Item->GetItemData()->Width;
	int32 ItemHeight = Item->GetItemData()->Height;

	for (int32 Y = StartY; Y < StartY + ItemHeight; Y++)
	{
		for (int32 X = StartX; X < StartX + ItemWidth; X++)
		{
			if (IsValidPosition(X, Y))
			{
				int32 Index = GetSlotIndex(X, Y);
				InventorySlots[Index].Item = Item;

			}
		}
	}
}

void UInventoryComponent::ClearItemSlots(UBaseItem* Item)
{
	if (!Item) return;

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Item == Item)
		{
			Slot.Item = nullptr;
		}
	}
}

bool UInventoryComponent::FindFirstFitPosition(UBaseItem* Item, int32& OutX, int32& OutY) const
{
	if (!Item || !Item->GetItemData()) return false;

	for (int32 X = 0; X < InventoryWidth; X++)
	{
		for (int32 Y = 0; Y < InventoryHeight; Y++)
		{
			if (CanItemFitAt(Item, X, Y))
			{
				OutX = X;
				OutY = Y;
				return true;
			}
		}
	}

	return false;
}