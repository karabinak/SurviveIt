// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "InventoryWidget.h"
#include "PlayerWidget.h"
#include "HotbarWidget.h"

void APlayerHUD::CreateInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->InitializeWidget(InventoryComponent);
	}
}

void APlayerHUD::CreateHotbarWidget(UHotbarComponent* HotbarComponent)
{
	if (HotbarWidgetClass)
	{
		HotbarWidget = CreateWidget<UHotbarWidget>(GetWorld(), HotbarWidgetClass);
		HotbarWidget->AddToViewport();
		HotbarWidget->InitializeWidget(HotbarComponent);
	}
}

bool APlayerHUD::ToogleInventory()
{
	if (InventoryWidget)
	{
		if (InventoryWidget->ToggleInventory()) return true;
	}
	return false;
}


void APlayerHUD::CreatePlayerWidget()
{
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		PlayerWidget->AddToViewport();
	}
}