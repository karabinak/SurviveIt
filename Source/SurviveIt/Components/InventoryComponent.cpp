

#include "InventoryComponent.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Widgets/PlayerHUD.h"
#include "SurviveIt/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InventoryWidth = 7; // Column
	InventoryHeight = 4; // Row
}

bool UInventoryComponent::IsValidPosition(int32 Column, int32 Row) const
{
	return Column >= 0 && Column < InventoryWidth && Row >= 0 && Row < InventoryHeight;
}

bool UInventoryComponent::AddItemAt(UBaseItem* Item, int32 Column, int32 Row)
{
	if (!Item || Item->IsEmpty() /*|| !AreItemSlotsEmpty(Item, Column, Row)*/) return false;

	SetItemSlot(Item, Column, Row);
	//OnInventoryChanged.Broadcast();
	OnItemAdded.Broadcast(Item, FIntPoint(Column, Row));

	return true;
}

bool UInventoryComponent::AddItem(UBaseItem* Item)
{
	if (!Item || Item->IsEmpty()) return false;
	if (TryStackItem(Item) && Item->IsEmpty()) return true;

	// If we couldn't stack or there's still quantity left, find a position
	int32 FoundColumn = 0;
	int32 FoundRow = 0;

	if (FindFirstFitPosition(Item, FoundColumn, FoundRow))
	{
		UE_LOG(LogTemp, Warning, TEXT("Col %i, Row %i"), FoundColumn, FoundRow);
		return AddItemAt(Item, FoundColumn, FoundRow);
	}

	return false;
}

bool UInventoryComponent::TryStackItem(UBaseItem* Item)
{
	if (!Item || !Item->GetItemData()) return false;

	TArray<UBaseItem*> ExistingItems = GetAllItems();
	for (UBaseItem* ExistingItem : ExistingItems)
	{
		if (Item->CanStackWith(ExistingItem))
		{
			int32 TransferredAmount = ExistingItem->TryStackWith(Item);
			//OnInventoryChanged.Broadcast();
			OnQuantityChanged.Broadcast(ExistingItem);

			if (Item->IsEmpty())
			{
				return true;
			}
		}
	}

	return Item->IsEmpty();
}

UBaseItem* UInventoryComponent::RemoveItemAt(int32 Column, int32 Row)
{
	if (!IsValidPosition(Column, Row)) return nullptr;

	UBaseItem* Item = GetItemAt(Column, Row);
	if (Item)
	{
		ClearItemSlot(Item);
		OnItemRemoved.Broadcast(Item);
	}

	return Item;
}

UBaseItem* UInventoryComponent::GetItemAt(int32 Column, int32 Row) const
{
	if (!IsValidPosition(Column, Row)) return nullptr;

	int32 Index = GetSlotIndex(Column, Row);
	return InventorySlots[Index].Item;
}

bool UInventoryComponent::MoveItem(int32 FromColumn, int32 FromRow, int32 ToColumn, int32 ToRow)
{
	UBaseItem* SourceItem = GetItemAt(FromColumn, FromRow);
	UBaseItem* DestinationItem = GetItemAt(ToColumn, ToRow);

	if (!SourceItem) return false;

	if (!DestinationItem) /** Destination Slot is Empty  */
	{
		
		ClearItemSlot(SourceItem);
		SetItemSlot(SourceItem, ToColumn, ToRow);

		OnItemMoved.Broadcast(SourceItem, FIntPoint(ToColumn, ToRow));
		UE_LOG(LogTemp, Warning, TEXT("Move"));
		return true;
	}
	else /** Destination Slot is Occupied  */
	{
		ClearItemSlot(SourceItem);
		ClearItemSlot(DestinationItem);

		SetItemSlot(SourceItem, ToColumn, ToRow);
		SetItemSlot(DestinationItem, FromColumn, FromRow);

		OnItemSwitch.Broadcast(SourceItem, DestinationItem);

		UE_LOG(LogTemp, Warning, TEXT("Switch"));

		return true;
	}
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

	//OnInventoryChanged.Broadcast();
	OnInventoryCleared.Broadcast();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UInventoryComponent::Initialize()
{
	InventorySlots.Empty();
	InventorySlots.SetNum(InventoryWidth * InventoryHeight);

	for (int32 Row = 0; Row < InventoryHeight; Row++)
	{
		for (int32 Column = 0; Column < InventoryWidth; Column++)
		{
			int32 Index = GetSlotIndex(Column, Row);
			InventorySlots[Index] = FInventorySlot(Column, Row);
		}
	}

	APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwner());
	if (HUD && PC)
	{
		HUD->CreateMainInventoryWidget(this, PC->GetHotbarComponent());
	}
}

bool UInventoryComponent::AreItemSlotEmpty(int32 Column, int32 Row) const
{
	if (GetItemAt(Column, Row) == nullptr) return true;
	return false;
}

int32 UInventoryComponent::GetSlotIndex(int32 Column, int32 Row) const
{
	return Row * InventoryWidth + Column;
}

void UInventoryComponent::SetItemSlot(UBaseItem* Item, int32 Column, int32 Row)
{
	if (!Item || !Item->GetItemData()) return;

	if (IsValidPosition(Column, Row))
	{
		int32 Index = GetSlotIndex(Column, Row);
		InventorySlots[Index].Item = Item;
	}
}

void UInventoryComponent::ClearItemSlot(UBaseItem* Item)
{
	if (!Item) return;

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Item == Item)
		{
			Slot.Item = nullptr;
			return;
		}
	}
}

bool UInventoryComponent::FindFirstFitPosition(UBaseItem* Item, int32& OutColumn, int32& OutRow) const
{
	if (!Item || !Item->GetItemData()) return false;

	for (int32 Column = 0; Column < InventoryWidth; Column++)
	{
		for (int32 Row = 0; Row < InventoryHeight; Row++)
		{
			if (AreItemSlotEmpty(Column, Row))
			{
				OutColumn = Column;
				OutRow = Row;
				return true;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("All Reserved"));
	return false;
}