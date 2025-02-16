
#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"

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