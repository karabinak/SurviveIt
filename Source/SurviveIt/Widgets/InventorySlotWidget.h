// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UBaseItem;
class UImage;
//class UCanvasPanel;
class USizeBox;
//class UBorder;
class UTextBlock;

UENUM(BlueprintType)
enum class UInventoryType : uint8
{
	UIT_Inventory UMETA(DisplayName = "Inventory"),
	UIT_Hotbar UMETA(DisplayName = "Hotbar"),
	UIT_OtherInventory UMETA(DisplayName = "OtherInventory")
};

UCLASS()
class SURVIVEIT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bHotbarItem = false;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotData(int32 InColumn, int32 InRow, UBaseItem* InItem, float InTileSize, UInventoryType InInventoryType);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	void GetSlotPosition(int32& OutColumn, int32& OutRow) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UBaseItem* GetItem() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetQuantityText(int32 InQuantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetDragVisualSize(float ItemSize);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SlotColumn;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SlotRow;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UBaseItem* Item;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SlotSizeBoxDrag;

	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY()
	UInventoryType InventoryType;

	// Drag and Drop

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
