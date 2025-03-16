// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInteraction.generated.h"

//class AToolItem;
//class AResourceItem;
class UBaseItem;

UINTERFACE(MinimalAPI)
class UInventoryInteraction : public UInterface
{
	GENERATED_BODY()
};


class SURVIVEIT_API IInventoryInteraction
{
	GENERATED_BODY()

public:

    UFUNCTION(Category = "Inventory")
    virtual void OnItemDragStarted(UBaseItem* Item) = 0;

    UFUNCTION(Category = "Inventory")
    virtual void OnItemDragEnded(UBaseItem* Item, UUserWidget* DestinationWidget) = 0;

    UFUNCTION(Category = "Inventory")
    virtual bool CanAcceptItem(UBaseItem* Item) = 0;
};
