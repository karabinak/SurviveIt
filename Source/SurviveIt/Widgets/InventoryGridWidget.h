// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
//class UBorder;
class UInventorySlotWidget;
class UInventoryComponent;
class USizeBox;
class UHorizontalBox;

UCLASS()
class SURVIVEIT_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeWidget(class UInventoryComponent* InInventoryComponent, float PanelSize);

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//bool ToggleInventory();

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void ShowInventory();

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void HideInventory();

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//UCanvasPanel* GetInventoryCanvas() const { return InventoryCanvas; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	float GetTileSize() const { return TileSize; }

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<USizeBox> InventorySizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryCanvas;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventorySlotWidget> InventorySlotItem;

	/** Callbacks */
	UFUNCTION()
	void OnItemAdded(UBaseItem* Item, FIntPoint SlotPosition);

	UFUNCTION()
	void OnQuantityChanged(UBaseItem* Item);

	UFUNCTION()
	void OnItemMoved(UBaseItem* Item, FIntPoint NewPosition);

	UFUNCTION()
	void OnItemRemoved(UBaseItem* Item);

	void CreateEmptySlots();

	UInventorySlotWidget* FindSlotWidgetAt(int32 Column, int32 Row) const;


private:

	UPROPERTY()
	float TileSize = 45.f;

	UPROPERTY()
	TMap<FIntPoint, UInventorySlotWidget*> SlotWidgets;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
