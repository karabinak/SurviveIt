// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UBaseItem;
class UImage;
class UCanvasPanel;
class USizeBox;
class UBorder;
class UTextBlock;

UCLASS()
class SURVIVEIT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotData(int32 InX, int32 InY, UBaseItem* InItem);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	void GetSlotPosition(int32& OutX, int32& OutY) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UBaseItem* GetItem() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SlotX;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SlotY;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UBaseItem* Item;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SlotSizeBox;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateVisuals();

	// Drag and Drop

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
