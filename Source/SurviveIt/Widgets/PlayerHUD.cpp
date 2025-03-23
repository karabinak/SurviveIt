// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "MainInventoryWidget.h"
#include "PlayerWidget.h"
#include "HotbarWidget.h"
#include "InventoryGridWidget.h"

void APlayerHUD::CreateMainInventoryWidget(UInventoryComponent* InventoryComponent, UHotbarComponent* HotbarComponent)
{
	if (MainInventoryWidgetClass)
	{
		MainInventoryWidget = CreateWidget<UMainInventoryWidget>(GetWorld(), MainInventoryWidgetClass);
		MainInventoryWidget->AddToViewport();
		MainInventoryWidget->InitializeWidget(InventoryComponent, HotbarComponent);
	}
}

//void APlayerHUD::CreateHotbarWidget(UHotbarComponent* HotbarComponent)
//{
//	if (HotbarWidgetClass)
//	{
//		HotbarWidget = CreateWidget<UHotbarWidget>(GetWorld(), HotbarWidgetClass);
//		HotbarWidget->AddToViewport();
//		HotbarWidget->InitializeWidget(HotbarComponent);
//	}
//}

void APlayerHUD::CreatePlayerWidget()
{
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		PlayerWidget->AddToViewport();
	}
}

bool APlayerHUD::ToogleMainInventoryWidget()
{
	if (!MainInventoryWidget) return false;

	if (MainInventoryWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		MainInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		return false;
	}
	else
	{
		MainInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		return true;
	}
}

bool APlayerHUD::ToogleInventoryGridWidget()
{
	if (!InventoryGridWidget) return false;

	if (InventoryGridWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		InventoryGridWidget->SetVisibility(ESlateVisibility::Hidden);
		return false;
	}
	else
	{
		InventoryGridWidget->SetVisibility(ESlateVisibility::Visible);
		return true;
	}
}
