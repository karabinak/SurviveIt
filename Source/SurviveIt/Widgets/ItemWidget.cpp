
#include "ItemWidget.h"
#include "Components/TextBlock.h"

#include "SurviveIt/Items/ItemBase.h"
#include "SurviveIt/Items/ResourceItem.h"

void UItemWidget::InitializeItemProperties(AItemBase* Item)
{
	if (Item)
	{
		ItemIcon = Item->GetItemIcon();
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
	}
}
