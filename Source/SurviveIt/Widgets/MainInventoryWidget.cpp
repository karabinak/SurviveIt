// Fill out your copyright notice in the Description page of Project Settings.

#include "MainInventoryWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/PanelSlot.h"

#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Character/PlayerCharacter.h"
#include "SurviveIt/Components/InventoryComponent.h"
#include "SurviveIt/Components/HotbarComponent.h"
#include "InventoryDragDropOperation.h"
#include "InventoryGridWidget.h"
#include "HotbarWidget.h"
#include "PlayerHUD.h"

#include "SurviveIt/Helpers/CustomLogging.h"

void UMainInventoryWidget::InitializeWidget(UInventoryComponent* InInventoryComponent, UHotbarComponent* InHotbarComponent)
{
	InventoryComponent = InInventoryComponent;
	HotbarComponent = InHotbarComponent;

	FTimerHandle TimerHandle; // Delayed function by 0.1s
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainInventoryWidget::DelayedInitialize, 0.1f, false);
}

void UMainInventoryWidget::DelayedInitialize()
{
	checkf(InventoryComponent, TEXT("InventoryComponent is not Valid"));
	checkf(HotbarComponent, TEXT("HotbarComponent is not Valid"));

	FVector2D InventoryGridPanelSize = InventoryGrid->GetCachedGeometry().GetLocalSize();

	if (InventoryGridClass)
	{
		InventoryGridWidget = CreateWidget<UInventoryGridWidget>(GetWorld(), InventoryGridClass);
		InventoryGridWidget->InitializeWidget(InventoryComponent, InventoryGridPanelSize.X);

		UPanelSlot* PanelSlot = InventoryGrid->AddChild(InventoryGridWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot))
		{
			float TileSize = InventoryGridPanelSize.X / InventoryComponent->InventoryWidth;
			float GridSizeX = InventoryGridPanelSize.X;
			float GridSizeY = TileSize * InventoryComponent->InventoryHeight;

			CanvasSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
		}
	}

	if (HotbarClass)
	{
		HotbarWidget = CreateWidget<UHotbarWidget>(GetWorld(), HotbarClass);
		HotbarWidget->InitializeWidget(HotbarComponent, InventoryGridPanelSize.X);

		UPanelSlot* PanelSlot = HotbarCanvas->AddChild(HotbarWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot))
		{
			float TileSize = InventoryGridPanelSize.X / HotbarComponent->NumSlots;
			float GridSizeX = InventoryGridPanelSize.X;
			float GridSizeY = TileSize;

			CanvasSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
		}
	}

	//APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//if (HUD)
	//{

	//}
}

bool UMainInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Droped On MainInventory"));
	//UInventoryDragDropOperation* DragDrop = Cast<UInventoryDragDropOperation>(InOperation);
	//if (!DragDrop || !DragDrop->SourceItem) return false;

	//APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (PlayerCharacter)
	//{
	//	return PlayerCharacter->DropItemFromInventory(DragDrop->SourceItem);
	//}
	return false;
}