// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UInventoryWidget;
class UInventoryComponent;

UCLASS()
class SURVIVEIT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:

	void CreateInventoryWidget(UInventoryComponent* Owner);

	bool ToogleInventory();

	UInventoryWidget* GetInventoryWidget() { return InventoryWidget; }

private:

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UInventoryWidget* InventoryWidget;
	
};
