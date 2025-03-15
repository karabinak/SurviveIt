// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UInventoryWidget;
class UPlayerWidget;
class UHotbarWidget;
class UInventoryComponent;
class UHotbarComponent;

UCLASS()
class SURVIVEIT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:

	void CreateInventoryWidget(UInventoryComponent* Owner);
	void CreateHotbarWidget(UHotbarComponent* Owner);
	void CreatePlayerWidget();

	bool ToogleInventory();

	UInventoryWidget* GetInventoryWidget() { return InventoryWidget; }

private:

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UHotbarWidget> HotbarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UHotbarWidget* HotbarWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UPlayerWidget* PlayerWidget;
	
};
