// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarWidget.h"

#include "Components/HorizontalBox.h"

#include "SurviveIt/Components/HotbarComponent.h"
#include "InventorySlotWidget.h"

void UHotbarWidget::InitializeWidget(UHotbarComponent* InHotbarComponent)
{
	HotbarComponent = InHotbarComponent;

	if (HotbarComponent)
	{
		HotbarComponent->OnHotbarSlotChanged.AddDynamic(this, &UHotbarWidget::OnHotbarSlotChanged);
		HotbarComponent->OnHotbarSlotSelected.AddDynamic(this, &UHotbarWidget::OnHotbarSlotSelected);
	}
}

void UHotbarWidget::RefreshHotbar()
{
	if (!HotbarComponent || !HotbarBox) return;

	HotbarBox->ClearChildren();

	for (int32 i = 0; i < HotbarComponent->NumSlots; i++)
	{
		if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, HotbarSlotWidgetClass))
		{
			UBaseItem* Item = HotbarComponent->GetItemFromSlot(i);
			// TEMP 10.f;
			SlotWidget->SetSlotData(i, 0, Item, 10.f);

			HotbarBox->AddChild(SlotWidget);
		}
	}
}

void UHotbarWidget::OnHotbarSlotChanged(int32 SlotIndex)
{
	RefreshHotbar();
}

void UHotbarWidget::OnHotbarSlotSelected(int32 SlotIndex)
{
	for (int32 i = 0; i < HotbarBox->GetChildrenCount(); i++)
	{
		if (UInventorySlotWidget* SlotWidget = Cast<UInventorySlotWidget>(HotbarBox->GetChildAt(i)))
		{
			//SlotWidget->SetSelevted(i == SlotIndex);
		}
	}
}
