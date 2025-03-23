
#include "InventorySlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
//#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
//#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Items/ResourceItem.h"
#include "SurviveIt/Character/PlayerCharacter.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "SurviveIt/Components/HotbarComponent.h"
#include "HotbarWidget.h"
#include "InventoryDragDropOperation.h"

void UInventorySlotWidget::SetSlotData(int32 InColumn, int32 InRow, UBaseItem* InItem, float InTileSize, UInventoryType InInventoryType)
{
	SlotColumn = InColumn;
	SlotRow = InRow;
	Item = InItem;
    TileSize = InTileSize;
    InventoryType = InInventoryType;


    if (Item && ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(Item->GetItemData()->Icon);
        ItemIcon->SetOpacity(1.f);

        if (Item->IsStackable() && QuantityText)
        {
            QuantityText->SetText(FText::AsNumber(Item->GetQuantity()));
            QuantityText->SetVisibility(ESlateVisibility::Visible);
        }
        else if (QuantityText)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
    else
    {
        if (ItemIcon)
        {
            ItemIcon->SetBrushFromTexture(nullptr);
            ItemIcon->SetOpacity(0.f);
        }

        if (QuantityText)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void UInventorySlotWidget::SetDragVisualSize(float ItemSize)
{
    SlotSizeBoxDrag->SetWidthOverride(ItemSize);
    SlotSizeBoxDrag->SetHeightOverride(ItemSize);
}

void UInventorySlotWidget::GetSlotPosition(int32& OutColumn, int32& OutRow) const
{
    OutColumn = SlotColumn;
    OutRow = SlotRow;
}

UBaseItem* UInventorySlotWidget::GetItem() const
{
    return Item;
}

void UInventorySlotWidget::SetQuantityText(int32 InQuantity)
{
    QuantityText->SetText(FText::AsNumber(Item->GetQuantity()));
    QuantityText->SetVisibility(ESlateVisibility::Visible);
}


FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && Item)
	{
		return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return FReply::Unhandled();
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (!Item) return;

	UInventoryDragDropOperation* DragDropOp = NewObject<UInventoryDragDropOperation>();
	DragDropOp->SourceItem = Item;
	DragDropOp->SourceSlotX = SlotColumn;
	DragDropOp->SourceSlotY = SlotRow;
    DragDropOp->InventoryType = InventoryType;

	UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(this, GetClass());
	DragVisual->SetSlotData(SlotColumn, SlotRow, Item, TileSize, InventoryType);
    DragVisual->SetDragVisualSize(TileSize);
    DragVisual->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.f));
	DragDropOp->DefaultDragVisual = DragVisual;

	OutOperation = DragDropOp;

    /*SlotBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 0.3f, 0.5f));*/
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    UInventoryDragDropOperation* InventoryDragDrop = Cast<UInventoryDragDropOperation>(InOperation);
    if (!InventoryDragDrop || !InventoryDragDrop->SourceItem) return false;

    APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    if (!Character) return false;

    UHotbarComponent* HotbarComp = Character->GetHotbarComponent();
    UInventoryComponent* InventoryComp = Character->GetInventoryComponent();

    if (!InventoryComp || !HotbarComp) return false;

    UBaseItem* DragItem = InventoryDragDrop->SourceItem;
    UBaseItem* PreviousItem = nullptr;
    UInventoryType SourceType = InventoryDragDrop->InventoryType;
    UInventoryType TargetType = InventoryType;

    if (SourceType == TargetType) 
    {
        switch (SourceType)  /** Same Inventory Types */
        {
        case UInventoryType::UIT_Inventory:
            return InventoryComp->MoveItem(InventoryDragDrop->SourceSlotX, InventoryDragDrop->SourceSlotY, SlotColumn, SlotRow);

        case UInventoryType::UIT_Hotbar:
            return HotbarComp->SwapHotbarSlots(InventoryDragDrop->SourceSlotX, SlotColumn);

        default:
            return false;
        }
    }
    else
    {
        if (SourceType == UInventoryType::UIT_Inventory && TargetType == UInventoryType::UIT_Hotbar) /** Inventory to Hotbar */
        {
            PreviousItem = HotbarComp->GetItemFromSlot(SlotColumn);
            if (!InventoryComp->RemoveItemAt(InventoryDragDrop->SourceSlotX, InventoryDragDrop->SourceSlotY)) return false;

            bool Result = HotbarComp->SetItemInSlot(SlotColumn, DragItem);

            if (PreviousItem && Result) /** If there was an item in the hotbar slot, return it to inventory */
            {
                InventoryComp->AddItem(PreviousItem);
            }
            else if (!Result && DragItem) /** Operation failed, return item to inventory */
            {
                InventoryComp->AddItem(DragItem);
            }

            return Result;
        }
        else if (SourceType == UInventoryType::UIT_Hotbar && TargetType == UInventoryType::UIT_Inventory) /** Hotbar to Invnentory */
        {
            PreviousItem = InventoryComp->GetItemAt(SlotColumn, SlotRow);
            if (!HotbarComp->RemoveItemFromSlot(InventoryDragDrop->SourceSlotX)) return false;

            bool Result = InventoryComp->AddItemAt(DragItem, SlotColumn, SlotRow);

            if (PreviousItem && Result)
            {
                HotbarComp->SetItemInSlot(InventoryDragDrop->SourceSlotX, PreviousItem);
            }
            else if (!Result && DragItem)
            {
                HotbarComp->SetItemInSlot(InventoryDragDrop->SourceSlotX, DragItem);
            }

            return Result;
        }

        /** Future Inventory types */
    }

    return false;
}