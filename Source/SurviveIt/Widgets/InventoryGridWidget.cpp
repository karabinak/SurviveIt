// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryGridWidget.h"

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
#include "InventoryGridWidget.h"

#include "SurviveIt/Helpers/CustomLogging.h"

void UInventoryGridWidget::InitializeWidget(UInventoryComponent* InInventoryComponent, float PanelSize)
{
	if (!InInventoryComponent) return;
	InventoryComponent = InInventoryComponent;
	TileSize = PanelSize / InventoryComponent->InventoryWidth;

	InventoryComponent->OnItemAdded.AddDynamic(this, &UInventoryGridWidget::OnItemAdded);
	InventoryComponent->OnQuantityChanged.AddDynamic(this, &UInventoryGridWidget::OnQuantityChanged);
	InventoryComponent->OnItemMoved.AddDynamic(this, &UInventoryGridWidget::OnItemMoved);
	InventoryComponent->OnItemRemoved.AddDynamic(this, &UInventoryGridWidget::OnItemRemoved);

	//InventoryComponent->OnInventoryCleared.AddDynamic(this, &UInventoryGridWidget::OnInventoryCleared);

	CreateEmptySlots();
}

void UInventoryGridWidget::CreateEmptySlots()
{
	InventoryCanvas->ClearChildren();
	SlotWidgets.Empty();

	for (int32 Row = 0; Row < InventoryComponent->InventoryHeight; Row++)
	{
		for (int Column = 0; Column < InventoryComponent->InventoryWidth; Column++)
		{
			if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, InventorySlotItem))
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

UInventorySlotWidget* UInventoryGridWidget::FindSlotWidgetAt(int32 Column, int32 Row) const
{
	FIntPoint Position(Column, Row);

	if (SlotWidgets.Contains(Position))
	{
		return SlotWidgets[Position];
	}

	return nullptr;
}

void UInventoryGridWidget::OnItemAdded(UBaseItem* Item, FIntPoint SlotPosition)
{
	if (!Item || !InventoryComponent) return;

	UInventorySlotWidget* SlotWidget = FindSlotWidgetAt(SlotPosition.X, SlotPosition.Y);
	if (!SlotWidget) return;

	SlotWidget->SetSlotData(SlotPosition.X, SlotPosition.Y, Item, TileSize);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SlotWidget->Slot))
	{
		CanvasSlot->SetSize(FVector2D(TileSize));
	}
}

void UInventoryGridWidget::OnQuantityChanged(UBaseItem* Item)
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

void UInventoryGridWidget::OnItemMoved(UBaseItem* Item, FIntPoint NewPosition)
{
	if (!Item) return;

	FIntPoint OldPosition{ 0 };
	UInventorySlotWidget* OldSlot = nullptr;

	for (const TPair<FIntPoint, UInventorySlotWidget*>& Pair : SlotWidgets)
	{
		if (Pair.Value->GetItem() == Item)
		{
			OldPosition = Pair.Key;
			OldSlot = Pair.Value;
			break;
		}
	}

	if (!OldSlot) return;
	OldSlot->SetSlotData(OldPosition.X, OldPosition.Y, nullptr, TileSize); // Reset the old root slot

	OnItemAdded(Item, NewPosition);
}

void UInventoryGridWidget::OnItemRemoved(UBaseItem* Item)
{
	if (!Item) return;

	FIntPoint ItemPosition{ 0 };
	UInventorySlotWidget* SlotWidget = nullptr;

	for (const TPair<FIntPoint, UInventorySlotWidget*>& Pair : SlotWidgets)
	{
		if (Pair.Value->GetItem() == Item)
		{
			ItemPosition = Pair.Key;
			SlotWidget = Pair.Value;
			break;
		}
	}

	if (!SlotWidget) return;
	SlotWidget->SetSlotData(ItemPosition.X, ItemPosition.Y, nullptr, TileSize);
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Dropped On Grid"));
	//UInventoryDragDropOperation* DragDrop = Cast<UInventoryDragDropOperation>(InOperation);
	//if (!DragDrop || !DragDrop->SourceItem) return false;

	//APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (PlayerCharacter)
	//{
	//	return PlayerCharacter->DropItemFromInventory(DragDrop->SourceItem);
	//}
	return false;
}

//bool UInventoryGridWidget::ToggleInventory()
//{
//	if (GetVisibility() == ESlateVisibility::Visible)
//	{
//		HideInventory();
//		return false;
//	}
//	else
//	{
//		ShowInventory();
//		return true;
//	}
//}
//
//void UInventoryGridWidget::ShowInventory()
//{
//	SetVisibility(ESlateVisibility::Visible);
//}
//
//void UInventoryGridWidget::HideInventory()
//{
//	SetVisibility(ESlateVisibility::Hidden);
//}
