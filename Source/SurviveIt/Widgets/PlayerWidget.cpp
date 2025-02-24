
#include "PlayerWidget.h"

#include "Components/TextBlock.h"

void UPlayerWidget::UpdateItemName(FText InItemName)
{
	if (InItemName.ToString() == "")
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}

	ItemName->SetText(InItemName);
}	