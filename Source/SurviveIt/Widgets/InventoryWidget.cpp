// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/GridPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"


//#include "SurviveIt/Widgets/ItemWidget.h"
#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "InventorySlotWidget.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;

	// Delayed function by 0.1s
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UInventoryWidget::DelayedInitialize, 0.1f, false);
}

void UInventoryWidget::DelayedInitialize()
{
	if (!InventoryComponent) return;

	InventoryComponent->OnItemAdded.AddDynamic(this, &UInventoryWidget::OnItemAdded);
	InventoryComponent->OnQuantityChanged.AddDynamic(this, &UInventoryWidget::OnQuantityChanged);
	//InventoryComponent->OnItemRemoved.AddDynamic(this, &UInventoryWidget::OnItemRemoved);
	InventoryComponent->OnItemMoved.AddDynamic(this, &UInventoryWidget::OnItemMoved);
	//InventoryComponent->OnInventoryCleared.AddDynamic(this, &UInventoryWidget::OnInventoryCleared);

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryBorder->Slot))
	{
		TileSize = InventorySection->GetCachedGeometry().GetLocalSize().X / InventoryComponent->InventoryWidth;

		float GridSizeX = InventoryComponent->InventoryWidth * TileSize;
		float GridSizeY = InventoryComponent->InventoryHeight * TileSize;
		CanvasPanelSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
	}

	CreateEmptySlots();
}

void UInventoryWidget::CreateEmptySlots()
{
	for (int32 Row = 0; Row < InventoryComponent->InventoryHeight; Row++)
	{
		for (int Column = 0; Column < InventoryComponent->InventoryWidth; Column++)
		{
			if(UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, InventorySlotItem))
			{
				SlotWidget->SetSlotData(Column, Row, nullptr, TileSize);

				UCanvasPanelSlot* CanvasSlot = InventoryCanvas->AddChildToCanvas(SlotWidget);
				CanvasSlot->SetSize(FVector2D(TileSize));
				CanvasSlot->SetPosition(FVector2D(Column, Row) * TileSize);

				SlotWidgets.Add(SlotWidget);
			}
		}
	}
}

void UInventoryWidget::OnItemAdded(UBaseItem* Item, FIntPoint SlotDimension)
{
	if (!InventoryComponent) return;

	if (UInventorySlotWidget* ItemWidget = CreateWidget<UInventorySlotWidget>(this, InventorySlotItem))
	{
		float ItemWidth = TileSize * Item->GetItemData()->Width;
		float ItemHeight = TileSize * Item->GetItemData()->Height;
		ItemWidget->SetSlotData(SlotDimension.X, SlotDimension.Y, Item, TileSize);

		UCanvasPanelSlot* CanvasSlot = InventoryCanvas->AddChildToCanvas(ItemWidget);
		CanvasSlot->SetSize(FVector2D(ItemWidth, ItemHeight));
		CanvasSlot->SetPosition(FVector2D(SlotDimension.X, SlotDimension.Y) * TileSize);

		UE_LOG(LogTemp, Warning, TEXT("Position %f, %f"), SlotDimension.X * TileSize, SlotDimension.Y * TileSize);

		SlotWidgets.Add(ItemWidget);
	}
}

void UInventoryWidget::OnQuantityChanged(UBaseItem* Item)
{
	for (UInventorySlotWidget* ItemWidget : SlotWidgets)
	{
		if (ItemWidget->GetItem() == Item)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Found"));
			ItemWidget->SetQuantityText(Item->GetQuantity());
			return;
		}
	}
}

void UInventoryWidget::OnItemMoved(UBaseItem* Item, FIntPoint MoveDimension)
{
	for (UInventorySlotWidget* ItemWidget : SlotWidgets)
	{
		if (ItemWidget->GetItem() == Item)
		{
			int32 Column = 0;
			int32 Row = 0;
			ItemWidget->GetSlotPosition(Column, Row);

			ItemWidget->SetSlotData(Column, Row, nullptr, TileSize);

			OnItemAdded(Item, MoveDimension);
			return;
		}
	}
}



//void UInventoryWidget::RefreshGrid()
//{
//	if (!InventoryComponent || !InventoryBorder || !InventorySection) return;
//
//	InventoryCanvas->ClearChildren();
//
//	for (int32 Row = 0; Row < InventoryComponent->InventoryHeight; Row++)
//	{
//		for (int Column = 0; Column < InventoryComponent->InventoryWidth; Column++)
//		{
//			if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, InventorySlotItem))
//			{
//				UBaseItem* Item = InventoryComponent->GetItemAt(Column, Row);
//				SlotWidget->SetSlotData(Column, Row, Item);
//
//				UCanvasPanelSlot* CanvasSlot = InventoryCanvas->AddChildToCanvas(SlotWidget);
//				TileSize = InventorySection->GetCachedGeometry().GetLocalSize().X / InventoryComponent->InventoryWidth;
//				//float ItemWidth = Item->GetItemData()->Width * TileSize;
//				//float ItemHeight = Item->GetItemData()->Height * TileSize;
//				CanvasSlot->SetSize(FVector2D(50.f, 50.f));
//				CanvasSlot->SetPosition(FVector2D(Column, Row) * TileSize);
//
//				InventoryCanvas->AddChildToCanvas(SlotWidget);
//			}
//		}
//	}
//}

bool UInventoryWidget::ToggleInventory()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		HideInventory();
		return false;
	}
	else
	{
		ShowInventory();
		return true;
	}
}

void UInventoryWidget::ShowInventory()
{
	SetVisibility(ESlateVisibility::Visible);

	//OnInventoryChanged();
}

void UInventoryWidget::HideInventory()
{
	SetVisibility(ESlateVisibility::Hidden);
}

//void UInventoryWidget::OnInventoryChanged()
//{
//	RefreshGrid();
//}