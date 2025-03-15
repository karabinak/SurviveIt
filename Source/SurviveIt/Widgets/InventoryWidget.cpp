// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "SurviveIt/Widgets/InventoryDragDropOperation.h" // TEMP
#include "SurviveIt/Character/PlayerCharacter.h"
#include "InventorySlotWidget.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* InInventoryComponent)
{
	if (!InInventoryComponent) return;
	InventoryComponent = InInventoryComponent;

	FTimerHandle TimerHandle; // Delayed function by 0.1s
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UInventoryWidget::DelayedInitialize, 0.1f, false);
}

void UInventoryWidget::DelayedInitialize()
{
	if (!InventoryComponent) return;

	InventoryComponent->OnItemAdded.AddDynamic(this, &UInventoryWidget::OnItemAdded);
	InventoryComponent->OnQuantityChanged.AddDynamic(this, &UInventoryWidget::OnQuantityChanged);
	InventoryComponent->OnItemMoved.AddDynamic(this, &UInventoryWidget::OnItemMoved);
	InventoryComponent->OnItemRemoved.AddDynamic(this, &UInventoryWidget::OnItemRemoved);

	//InventoryComponent->OnInventoryCleared.AddDynamic(this, &UInventoryWidget::OnInventoryCleared);

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryBorder->Slot))
	{
		TileSize = InventorySection->GetCachedGeometry().GetLocalSize().X / InventoryComponent->InventoryWidth;

		float GridSizeX = InventoryComponent->InventoryWidth * TileSize;
		float GridSizeY = InventoryComponent->InventoryHeight * TileSize;
		CanvasPanelSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
		SetVisibility(ESlateVisibility::Hidden);
	}

	CreateEmptySlots();
}

void UInventoryWidget::CreateEmptySlots()
{
	InventoryCanvas->ClearChildren();
	SlotWidgets.Empty();

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

				SlotWidgets.Add(FIntPoint(Column, Row), SlotWidget);
			}
		}
	}
}

UInventorySlotWidget* UInventoryWidget::FindSlotWidgetAt(int32 Column, int32 Row) const
{
	FIntPoint Position(Column, Row);

	if (SlotWidgets.Contains(Position))
	{
		return SlotWidgets[Position];
	}

	return nullptr;
}

void UInventoryWidget::UpdateCoveredSlots(int32 StartColumn, int32 StartRow, int32 Width, int32 Height, bool bHide)
{
	for (int32 Row = StartRow; Row < StartRow + Height; Row++)
	{
		for (int32 Column = StartColumn; Column < StartColumn + Width; Column++)
		{
			// Skip the root slot (top-left corner)
			if (Column == StartColumn && Row == StartRow) continue;

			if (UInventorySlotWidget* SlotWidget = FindSlotWidgetAt(Column, Row))
			{
				SlotWidget->SetVisibility(bHide ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
			}
		}
	}
}

void UInventoryWidget::OnItemAdded(UBaseItem* Item, FIntPoint SlotPosition)
{
	if (!Item || !InventoryComponent) return;

	UInventorySlotWidget* RootSlotWidget = FindSlotWidgetAt(SlotPosition.X, SlotPosition.Y);
	if (!RootSlotWidget) return;

	int32 ItemWidth = Item->GetItemData()->Width;
	int32 ItemHeight = Item->GetItemData()->Height;

	RootSlotWidget->SetSlotData(SlotPosition.X, SlotPosition.Y, Item, TileSize);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(RootSlotWidget->Slot))
	{
		CanvasSlot->SetSize(FVector2D(ItemWidth, ItemHeight) * TileSize);
	}

	UpdateCoveredSlots(SlotPosition.X, SlotPosition.Y, ItemWidth, ItemHeight, true);
}

void UInventoryWidget::OnQuantityChanged(UBaseItem* Item)
{
	if (!Item) return;

	for (const TPair<FIntPoint, UInventorySlotWidget*>& Pair : SlotWidgets)
	{
		if (Pair.Value->GetItem() == Item)
		{
			Pair.Value->SetQuantityText(Item->GetQuantity());
			return;
		}
	}
}

void UInventoryWidget::OnItemMoved(UBaseItem* Item, FIntPoint NewPosition)
{
	if (!Item) return;

	FIntPoint OldPosition{0};
	UInventorySlotWidget* OldRootSlot = nullptr;

	for (const TPair<FIntPoint, UInventorySlotWidget*>& Pair : SlotWidgets)
	{
		if (Pair.Value->GetItem() == Item)
		{
			OldPosition = Pair.Key;
			OldRootSlot = Pair.Value;
			break;
		}
	}

	if (!OldRootSlot) return;

	const int32 ItemWidth = Item->GetItemData()->Width;
	const int32 ItemHeight = Item->GetItemData()->Height;

	OldRootSlot->SetSlotData(OldPosition.X, OldPosition.Y, nullptr, TileSize); // Reset the old root slot

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(OldRootSlot->Slot)) // Reset the old slot's size to 1x1
	{
		CanvasSlot->SetSize(FVector2D(TileSize, TileSize));
	}

	UpdateCoveredSlots(OldPosition.X, OldPosition.Y, ItemWidth, ItemHeight, false);

	OnItemAdded(Item, NewPosition);
}

void UInventoryWidget::OnItemRemoved(UBaseItem* Item)
{
	if (!Item) return;

	FIntPoint ItemPosition{ 0 };
	UInventorySlotWidget* RootSlotWidget = nullptr;

	for (const TPair<FIntPoint, UInventorySlotWidget*>& Pair : SlotWidgets)
	{
		if (Pair.Value->GetItem() == Item)
		{
			ItemPosition = Pair.Key;
			RootSlotWidget = Pair.Value;
			break;
		}
	}

	if (!RootSlotWidget) return;

	const int32 ItemWidth = Item->GetItemData()->Width;
	const int32 ItemHeight = Item->GetItemData()->Height;

	RootSlotWidget->SetSlotData(ItemPosition.X, ItemPosition.Y, nullptr, TileSize);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(RootSlotWidget->Slot))
	{
		CanvasSlot->SetSize(FVector2D(TileSize));
	}

	UpdateCoveredSlots(ItemPosition.X, ItemPosition.Y, ItemWidth, ItemHeight, false);
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragDropOperation* DragDrop = Cast<UInventoryDragDropOperation>(InOperation);
	if (!DragDrop || !DragDrop->SourceItem) return false;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		return PlayerCharacter->DropItemFromInventory(DragDrop->SourceItem);
	}
	return false;
}

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