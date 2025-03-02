
#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Items/ResourceItem.h"

//void UItemWidget::InitializeItemProperties(UBaseItem* Item)
//{
//	if (Item)
//	{
//		ItemIcon->SetBrushFromTexture(Item->GetItemIcon());
//		if (AResourceItem* ResourceItem = Cast<AResourceItem>(Item))
//		{
//			QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%i"), ResourceItem->GetResourceQuantity())));
//		}
//	}
//}
//
//void UItemWidget::UpdateProperties(UBaseItem* Item)
//{
//	if (AResourceItem* ResourceItem = Cast<AResourceItem>(Item))
//	{
//		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%i"), ResourceItem->GetResourceQuantity())));
//		ItemIcon->SetBrushFromTexture(Item->GetItemIcon());
//	}
//}
//
//void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	ItemBorder->SetBrushColor(FLinearColor(.09f, .245f, .05f, .2f));
//
//	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Blue, FString::Printf(TEXT("%s"), *GetName()));
//}
//
//void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
//{
//	ItemBorder->SetBrushColor(FLinearColor(.05f, .07f, .245f, .2f));
//}