// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UMainInventoryWidget;
class UPlayerWidget;
class UHotbarWidget;
class UInventoryComponent;
class UHotbarComponent;
class UInventoryGridWidget;

UCLASS()
class SURVIVEIT_API APlayerHUD : public AHUD
{

	GENERATED_BODY()

public:
	void CreateMainInventoryWidget(UInventoryComponent* Owner);
	UInventoryGridWidget* CreateInventoryGridWidget(UInventoryComponent* Owner);

	void CreateHotbarWidget(UHotbarComponent* Owner);
	void CreatePlayerWidget();

	//bool ToogleInventory();
	bool ToogleMainInventoryWidget();
	bool ToogleInventoryGridWidget();

	UMainInventoryWidget* GetInventoryWidget() { return MainInventoryWidget; }

private:

	/** Inventory widgets */
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UMainInventoryWidget> MainInventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UMainInventoryWidget* MainInventoryWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UInventoryGridWidget> InventoryGridClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UInventoryGridWidget* InventoryGridWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UHotbarWidget> HotbarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UHotbarWidget* HotbarWidget;


	/** Inventory widgets */

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UPlayerWidget* PlayerWidget;

	
};
