// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEIT_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UBaseItem* SourceItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 SourceSlotX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 SourceSlotY;
	
};
