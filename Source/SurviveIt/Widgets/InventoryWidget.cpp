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

//void UInventoryWidget::InitializeGrid(float SlotSize, int32 Rows, int32 Columns)
//{
//	float GridSizeX = SlotSize * Columns;
//	float GridSizeY = SlotSize * Rows;
//
//	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryBorder->Slot))
//	{
//		CanvasPanelSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
//	}
//}

//void UInventoryWidget::AddItemToWidget(FVector2D FirstTile, float SlotSize, UBaseItem* Item)
//{
//	if (ItemWidgetClass)
//	{
//		UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
//		float ItemWidth = SlotSize * Item->GetItemWidth();
//		float ItemHeight = SlotSize * Item->GetItemHeight();
//		ItemWidget->InitializeItemProperties(Item);
//		ItemWidget->SetItemBase(Item);
//		Item->SetItemWidget(ItemWidget);
//
//		UCanvasPanelSlot* CanvasSlot = InventoryCanvas->AddChildToCanvas(ItemWidget);
//		CanvasSlot->SetSize(FVector2D(ItemWidth, ItemHeight));
//		CanvasSlot->SetPosition(FVector2D(FirstTile.Y, FirstTile.X) * SlotSize);
//
//		ItemWidgetArray.Add(ItemWidget);
//	}
//}

//void UInventoryWidget::RemoveWidget(UItemWidget* InWidget)
//{
//	if (ItemWidgetArray.Contains(InWidget))
//	{
//		ItemWidgetArray[ItemWidgetArray.Find(InWidget)]->RemoveFromParent();
//	}
//}

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
			if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, UInventorySlotWidget::StaticClass()))
			{
				UBaseItem* Item = InventoryComponent->GetItemAt(X, Y);
				SlotWidget->SetSlotData(X, Y, Item);

				InventoryGrid->AddChildToGrid(SlotWidget, Y, X);
			}
		}
	}
}

void UInventoryWidget::OnInventoryChanged()
{
	RefreshGrid();
}
