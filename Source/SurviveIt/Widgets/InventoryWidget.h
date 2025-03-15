// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UBorder;
//class UItemWidget;
class UInventorySlotWidget;
class UInventoryComponent;
//class UGridPanel;
class USizeBox;
class UHorizontalBox;
//class UVerticalBox;

UCLASS()
class SURVIVEIT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeWidget(UInventoryComponent* InInventoryComponent);

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void RefreshGrid();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HideInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DelayedInitialize();

protected:

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    UInventoryComponent* InventoryComponent;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* MainInventoryHorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* PlayerSection;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventorySection;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* FunctionalSection;

	UPROPERTY(meta = (BindWidget))
	UBorder* InventoryBorder;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventoryCanvas;

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

	//UFUNCTION()
	//void OnInventoryCleared();

	//UFUNCTION()
	//void OnInventoryItemRemoved();


	void CreateEmptySlots();

	UInventorySlotWidget* FindSlotWidgetAt(int32 Column, int32 Row) const;

	void UpdateCoveredSlots(int32 StartColumn, int32 StartRow, int32 Width, int32 Height, bool bHide);

private:

	UPROPERTY()
	float TileSize = 10.f;

	//UPROPERTY()
	//TArray<UInventorySlotWidget*> SlotWidgets;

	UPROPERTY()
	TMap<FIntPoint, UInventorySlotWidget*> SlotWidgets;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
