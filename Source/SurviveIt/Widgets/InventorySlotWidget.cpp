
#include "InventorySlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
//#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Items/ResourceItem.h"
#include "SurviveIt/Character/PlayerCharacter.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "InventoryDragDropOperation.h"

void UInventorySlotWidget::SetSlotData(int32 InColumn, int32 InRow, UBaseItem* InItem, float InTileSize)
{
	SlotColumn = InColumn;
	SlotRow = InRow;
	Item = InItem;
    TileSize = InTileSize;

    SlotSizeBox->SetWidthOverride(TileSize);
    SlotSizeBox->SetHeightOverride(TileSize);

    if (Item && ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(Item->GetItemData()->Icon);
        ItemIcon->SetOpacity(1.f);

        const float ItemWidth = Item->GetItemData()->Width * TileSize;
        const float ItemHeight = Item->GetItemData()->Height * TileSize;
        SlotSizeBox->SetWidthOverride(ItemWidth);
        SlotSizeBox->SetHeightOverride(ItemHeight);

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

	UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(this, GetClass());
	DragVisual->SetSlotData(SlotColumn, SlotRow, Item, TileSize);
	DragDropOp->DefaultDragVisual = DragVisual;

	OutOperation = DragDropOp;
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    UInventoryDragDropOperation* InventoryDragDrop = Cast<UInventoryDragDropOperation>(InOperation);
    if (!InventoryDragDrop) return false;

    APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    if (!Character) return false;

    UInventoryComponent* InventoryComp = Character->GetInventoryComponent();
    if (!InventoryComp) return false;

    return InventoryComp->MoveItem(InventoryDragDrop->SourceSlotX, InventoryDragDrop->SourceSlotY, SlotColumn, SlotRow);
}