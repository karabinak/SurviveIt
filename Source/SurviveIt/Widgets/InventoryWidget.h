// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

//class UBorder;
//class UCanvasPanel;
//class UBaseItem;
class UItemWidget;
class UInventorySlotWidget;
class UInventoryComponent;
class UGridPanel;

UCLASS()
class SURVIVEIT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeWidget(UInventoryComponent* InInventoryComponent);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshGrid();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HideInventory();

protected:

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    UInventoryComponent* InventoryComponent;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* InventoryGrid;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventorySlotWidget> InventorySlotItem;

	UFUNCTION()
	void OnInventoryChanged();

	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:

	//UPROPERTY(meta = (BindWidget))
	//UBorder* InventoryBorder;

	//UPROPERTY(meta = (BindWidget))
	//UCanvasPanel* InventoryCanvas;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UUserWidget> ItemWidgetClass;

	//UPROPERTY(EditAnywhere)
	//TArray<UItemWidget*> ItemWidgetArray;

public:

	//void InitializeGrid(float SlotSize, int32 Rows, int32 Columns);

	//void AddItemToWidget(FVector2D FirstTile, float SlotSize, UBaseItem* Item);
	//void RemoveWidget(UItemWidget* InWidget);

};
