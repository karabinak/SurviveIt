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
#include "InventoryDragDropOperation.h"
#include "InventoryGridWidget.h"
#include "PlayerHUD.h"

#include "SurviveIt/Helpers/CustomLogging.h"

void UMainInventoryWidget::InitializeWidget(UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;

	FTimerHandle TimerHandle; // Delayed function by 0.1s
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainInventoryWidget::DelayedInitialize, 0.1f, false);
}

void UMainInventoryWidget::DelayedInitialize()
{
	checkf(InventoryComponent, TEXT("InventoryComponent is not Valid"));

	FVector2D InventoryGridPanel = InventoryGrid->GetCachedGeometry().GetLocalSize();

	if (InventoryGridClass)
	{
		InventoryGridWidget = CreateWidget<UInventoryGridWidget>(GetWorld(), InventoryGridClass);
		InventoryGridWidget->InitializeWidget(InventoryComponent, InventoryGridPanel.X);

		UPanelSlot* PanelSlot = InventoryGrid->AddChild(InventoryGridWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot))
		{
			float TileSize = InventoryGridPanel.X / InventoryComponent->InventoryWidth;
			float GridSizeX = InventoryGridPanel.X;
			float GridSizeY = TileSize * InventoryComponent->InventoryHeight;

			CanvasSlot->SetSize(FVector2D(GridSizeX, GridSizeY));
		}
	}

	APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (HUD)
	{

	}
}


//bool UMainInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Droped On MainInventory"));
//	UInventoryDragDropOperation* DragDrop = Cast<UInventoryDragDropOperation>(InOperation);
//	if (!DragDrop || !DragDrop->SourceItem) return false;
//
//	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	if (PlayerCharacter)
//	{
//		return PlayerCharacter->DropItemFromInventory(DragDrop->SourceItem);
//	}
//	return false;
//}