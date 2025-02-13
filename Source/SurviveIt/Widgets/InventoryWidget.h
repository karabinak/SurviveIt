// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UBorder;
class UCanvasPanel;
class AItemBase;
class UItemWidget;

UCLASS()
class SURVIVEIT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:



protected:

	

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

	void InitializeGrid(float SlotSize, int32 Rows, int32 Columns);

	void AddItemToWidget(FVector2D FirstTile, float SlotSize, AItemBase* Item);

};
