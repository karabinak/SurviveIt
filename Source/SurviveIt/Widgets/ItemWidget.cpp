
#include "ItemWidget.h"

#include "SurviveIt/Items/ItemBase.h"

void UItemWidget::InitializeItemProperties(AItemBase* Item)
{
	if (Item)
	{
		ItemIcon = Item->GetItemIcon();
	}
}
