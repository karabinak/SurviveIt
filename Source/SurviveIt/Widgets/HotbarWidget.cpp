// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"

#include "SurviveIt/Components/HotbarComponent.h"
#include "InventorySlotWidget.h"

void UHotbarWidget::InitializeWidget(UHotbarComponent* InHotbarComponent, float PanelSize)
{
	if (!InHotbarComponent) return;
	HotbarComponent = InHotbarComponent;
	TileSize = PanelSize / HotbarComponent->NumSlots;

	FTimerHandle TimerHandle; // Delayed function by 0.1s
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHotbarWidget::DelayedInitialize, 0.1f, false);

}

void UHotbarWidget::DelayedInitialize()
{

	if (HotbarComponent)
	{
		HotbarComponent->OnHotbarSlotChanged.AddDynamic(this, &UHotbarWidget::OnHotbarSlotChanged);
		HotbarComponent->OnHotbarSlotSelected.AddDynamic(this, &UHotbarWidget::OnHotbarSlotSelected);
	}

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(HotbarBorder->Slot))
	{
		TileSize = HotbarBorder->GetCachedGeometry().GetLocalSize().X / HotbarComponent->NumSlots;

		float GridSizeX = HotbarComponent->NumSlots * TileSize;
		float GridSizeY = TileSize;
		CanvasPanelSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
	}

	CreateEmptySlots();
}

void UHotbarWidget::ShowHotbar()
{
	SetVisibility(ESlateVisibility::Visible);

	if (HotbarComponent)
	{
		for (int32 i = 0; i < HotbarComponent->NumSlots; i++)
		{
			OnHotbarSlotChanged(i);
		}

		// Show selection
		OnHotbarSlotSelected(HotbarComponent->SelectedSlot);
	}
}

void UHotbarWidget::CreateEmptySlots()
{
	HotbarCanvas->ClearChildren();
	HotbarWidgets.Empty();

	for (int32 Size = 0; Size < HotbarComponent->NumSlots; Size++)
	{
		if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, HotbarSlotItem))
		{
			SlotWidget->SetSlotData(Size, 0, nullptr, TileSize, UInventoryType::UIT_Hotbar);
			SlotWidget->bHotbarItem = true;

			UCanvasPanelSlot* CanvasSlot = HotbarCanvas->AddChildToCanvas(SlotWidget);
			CanvasSlot->SetSize(FVector2D(TileSize));
			CanvasSlot->SetPosition(FVector2D(Size, 0.f) * TileSize);

			HotbarWidgets.Add(Size, SlotWidget);
		}
	}
}

void UHotbarWidget::OnHotbarSlotChanged(int32 SlotIndex)
{
	if (!HotbarComponent || !HotbarWidgets.Contains(SlotIndex)) return;

	UBaseItem* Item = HotbarComponent->GetItemFromSlot(SlotIndex);
	UInventorySlotWidget* SlotWidget = HotbarWidgets[SlotIndex];

	SlotWidget->SetSlotData(SlotIndex, 0, Item, TileSize, UInventoryType::UIT_Hotbar);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SlotWidget->Slot))
	{
		CanvasSlot->SetSize(FVector2D(TileSize));
	}

	if (SlotIndex == HotbarComponent->SelectedSlot)
	{
		OnHotbarSlotSelected(SlotIndex);
	}
}

void UHotbarWidget::OnHotbarSlotSelected(int32 SlotIndex)
{
	for (auto& Pair : HotbarWidgets)
	{
		if (UBorder* Border = Cast<UBorder>(Pair.Value->GetRootWidget()))
		{
			Border->SetBrushColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}

	if (HotbarWidgets.Contains(SlotIndex))
	{
		if (UBorder* Border = Cast<UBorder>(HotbarWidgets[SlotIndex]->GetRootWidget()))
		{
			Border->SetBrushColor(FLinearColor(1.0f, 0.8f, 0.0f, 0.7f));
		}
	}
}

bool UHotbarWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Dropped On Hotbar"));
	//UInventoryDragDropOperation* DragDrop = Cast<UInventoryDragDropOperation>(InOperation);
	//if (!DragDrop || !DragDrop->SourceItem) return false;

	//APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (PlayerCharacter)
	//{
	//	return PlayerCharacter->DropItemFromInventory(DragDrop->SourceItem);
	//}
	return false;
}
