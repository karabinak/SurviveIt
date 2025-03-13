// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "InventoryWidget.h"

void APlayerHUD::CreateInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->InitializeWidget(InventoryComponent);
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
