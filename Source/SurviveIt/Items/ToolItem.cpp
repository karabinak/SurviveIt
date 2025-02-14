// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"

bool AToolItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
    if (InventoryHandler->AddToolToInventory(this))
    {
        return true;
    }
    return false;
}
