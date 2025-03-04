// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/GridPanel.h"

//#include "SurviveIt/Widgets/ItemWidget.h"
#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "InventorySlotWidget.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;

	if (InventoryComponent)
	{
		InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryWidget::OnInventoryChanged);
	}
}

void UInventoryWidget::RefreshGrid()
{
	if (!InventoryComponent || !InventoryGrid) return;

	InventoryGrid->ClearChildren();

	for (int32 Y = 0; Y < InventoryComponent->InventoryHeight; Y++)
	{
		for (int X = 0; X < InventoryComponent->InventoryWidth; X++)
		{
			if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, InventorySlotItem))
			{
				UBaseItem* Item = InventoryComponent->GetItemAt(X, Y);
				SlotWidget->SetSlotData(X, Y, Item);

				InventoryGrid->AddChildToGrid(SlotWidget, Y, X);
			}
		}
	}
}

void UInventoryWidget::ToggleInventory()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		HideInventory();
	}
	else
	{
		ShowInventory();
	}
}

void UInventoryWidget::ShowInventory()
{
	SetVisibility(ESlateVisibility::Visible);

	OnInventoryChanged();
}

void UInventoryWidget::HideInventory()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::OnInventoryChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("InvChanged"));
	RefreshGrid();
}
