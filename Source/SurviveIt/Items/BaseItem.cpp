
#include "BaseItem.h"
#include "Components/BoxComponent.h"

UItemData::UItemData()
{
	Name = FText::FromString("Item");
	Description = FText::FromString("An item");
	MaxStackSize = 1;
	ItemType = EItemType::EIT_Resources;
	bIsStackable = true;
}

UBaseItem::UBaseItem()
{
	ItemData = nullptr;
	Quantity = 0;
}

void UBaseItem::Initialize(UItemData* InItemData, int32 InQuantity)
{
	if (InItemData)
	{
		ItemData = InItemData;
		Quantity = FMath::Clamp(InQuantity, 0, ItemData->MaxStackSize);
	}
}

UItemData* UBaseItem::GetItemData() const
{
	return ItemData;
}

int32 UBaseItem::GetQuantity() const
{
	return Quantity;
}

void UBaseItem::SetQuantity(int32 NewQuantity)
{
	if (ItemData)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemData->MaxStackSize);
	}
	else
	{
		Quantity = 0;
	}
}

int32 UBaseItem::AddQuantity(int32 AmountToAdd)
{
	if (ItemData == nullptr || AmountToAdd <= 0) return 0;

	int32 OriginalQuantity = Quantity;
	Quantity = FMath::Clamp(Quantity + AmountToAdd, 0, ItemData->MaxStackSize);
	return Quantity - OriginalQuantity;
}

int32 UBaseItem::RemoveQuantity(int32 AmountToRemove)
{
	if (ItemData == nullptr || AmountToRemove <= 0) return 0;

	int32 OriginalQuantity = Quantity;
	Quantity = FMath::Clamp(Quantity - AmountToRemove, 0, ItemData->MaxStackSize);
	return Quantity - OriginalQuantity;
}

bool UBaseItem::CanStackWith(UBaseItem* OtherItem) const
{
	if (ItemData == nullptr || !ItemData->bIsStackable) return false;
	if (OtherItem == nullptr || OtherItem->ItemData == nullptr || !OtherItem->ItemData->bIsStackable) return false;

	return ItemData == OtherItem->ItemData && Quantity < ItemData->MaxStackSize;
}

int32 UBaseItem::TryStackWith(UBaseItem* OtherItem)
{
	if (!CanStackWith(OtherItem)) return 0;

	int32 SpaceInStack = ItemData->MaxStackSize - Quantity;
	int32 AmountToTransfer = FMath::Min(SpaceInStack, OtherItem->Quantity);

	Quantity += AmountToTransfer;
	OtherItem->Quantity -= AmountToTransfer;

	return AmountToTransfer;
}

UBaseItem* UBaseItem::SplitStack(int32 SplitQuantity)
{
	if (ItemData == nullptr || !ItemData->bIsStackable || SplitQuantity <= 0 || SplitQuantity >= Quantity) return nullptr;

	UBaseItem* NewItem = NewObject<UBaseItem>();
	NewItem->Initialize(ItemData, SplitQuantity);

	return NewItem;
}

bool UBaseItem::Use(AActor* User)
{
	return false;
}

bool UBaseItem::IsEmpty() const
{
	return Quantity <= 0;
}

bool UBaseItem::IsStackable() const
{
	if (ItemData == nullptr) return false;
	return ItemData->bIsStackable;
}