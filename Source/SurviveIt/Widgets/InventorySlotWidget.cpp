
#include "InventorySlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Items/ResourceItem.h"
#include "SurviveIt/Character/PlayerCharacter.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "InventoryDragDropOperation.h"

void UInventorySlotWidget::SetSlotData(int32 InX, int32 InY, UBaseItem* InItem)
{
	SlotX = InX;
	SlotY = InY;
	Item = InItem;

    if (Item && ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(Item->GetItemData()->Icon);

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
        }

        if (QuantityText)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    UpdateVisuals();
}

void UInventorySlotWidget::GetSlotPosition(int32& OutX, int32& OutY) const
{
    OutX = SlotX;
    OutY = SlotY;
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
	DragDropOp->SourceSlotX = SlotX;
	DragDropOp->SourceSlotY = SlotY;

	UInventorySlotWidget* DragVisual = CreateWidget<UInventorySlotWidget>(this, GetClass());
	DragVisual->SetSlotData(SlotX, SlotY, Item);
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

    return InventoryComp->MoveItem(InventoryDragDrop->SourceSlotX, InventoryDragDrop->SourceSlotY, SlotX, SlotY);
}