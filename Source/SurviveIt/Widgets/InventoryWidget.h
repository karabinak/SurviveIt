// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UBorder;
class UCanvasPanel;
class UBaseItem;
class UItemWidget;

UCLASS()
class SURVIVEIT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:



protected:

	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:

	UPROPERTY(meta = (BindWidget))
	UBorder* InventoryBorder;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventoryCanvas;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere)
	TArray<UItemWidget*> ItemWidgetArray;

public:

	//void InitializeGrid(float SlotSize, int32 Rows, int32 Columns);

	//void AddItemToWidget(FVector2D FirstTile, float SlotSize, UBaseItem* Item);
	//void RemoveWidget(UItemWidget* InWidget);

};
