
#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "SurviveIt/Items/ItemBase.h"
#include "SurviveIt/Items/ResourceItem.h"

void UItemWidget::InitializeItemProperties(AItemBase* Item)
{
	if (Item)
	{
		ItemIcon->SetBrushFromTexture(Item->GetItemIcon());
		if (AResourceItem* ResourceItem = Cast<AResourceItem>(Item))
		{
			QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%i"), ResourceItem->GetResourceQuantity())));
		}
	}
}

void UItemWidget::UpdateProperties(AItemBase* Item)
{
	if (AResourceItem* ResourceItem = Cast<AResourceItem>(Item))
	{
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%i"), ResourceItem->GetResourceQuantity())));
		ItemIcon->SetBrushFromTexture(Item->GetItemIcon());
	}
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ItemBorder->SetBrushColor(FLinearColor(.09f, .245f, .05f, .2f));
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	ItemBorder->SetBrushColor(FLinearColor(.05f, .07f, .245f, .2f));
}



//FReply UItemWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//	UE_LOG(LogTemp, Warning, TEXT("PressDown"));
//	return FReply::Handled();
//}

//FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
//	{
//		UDragItemOperation* DragOperation = NewObject<UDragItemOperation>();
//		DragOperation->OriginSlotWidget = this;
//		DragOperation->ItemData = ItemData;
//		DragOperation->DefaultDragVisual = CreateDragVisualWidget();
//
//		UE_LOG(LogTemp, Warning, TEXT("LMB Drag"));
//		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
//	}
//	UE_LOG(LogTemp, Warning, TEXT("No LMB"));
//	return FReply::Unhandled();
//}
//
//UWidget* UItemWidget::CreateDragVisualWidget()
//{
//	UUserWidget* DragVisual = CreateWidget<UUserWidget>(GetWorld(), DragVisualClass);
//	DragVisual->SetColorAndOpacity(FLinearColor(1, 1, 1, 0.7f));
//	return DragVisual;
//}
