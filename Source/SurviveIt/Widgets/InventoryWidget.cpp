// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"

#include "SurviveIt/Widgets/ItemWidget.h"
#include "SurviveIt/Items/ItemBase.h"

void UInventoryWidget::InitializeGrid(float SlotSize, int32 Rows, int32 Columns)
{
	float GridSizeX = SlotSize * Columns;
	float GridSizeY = SlotSize * Rows;

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryBorder->Slot))
	{
		CanvasPanelSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
	}
}

void UInventoryWidget::AddItemToWidget(FVector2D FirstTile, float SlotSize, AItemBase* Item)
{
	if (ItemWidgetClass)
	{
		UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
		float ItemWidth = SlotSize * Item->GetItemWidth();
		float ItemHeight = SlotSize * Item->GetItemHeight();
		ItemWidget->InitializeItemProperties(Item);
		ItemWidget->SetItemBase(Item);
		Item->SetItemWidget(ItemWidget);

		UCanvasPanelSlot* CanvasSlot = InventoryCanvas->AddChildToCanvas(ItemWidget);
		CanvasSlot->SetSize(FVector2D(ItemWidth, ItemHeight));
		CanvasSlot->SetPosition(FVector2D(FirstTile.Y, FirstTile.X) * SlotSize);

		ItemWidgetArray.Add(ItemWidget);
	}
}

void UInventoryWidget::RemoveWidget(UItemWidget* InWidget)
{
	if (ItemWidgetArray.Contains(InWidget))
	{
		ItemWidgetArray[ItemWidgetArray.Find(InWidget)]->RemoveFromParent();
	}
}
