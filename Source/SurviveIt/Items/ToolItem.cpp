// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
//#include "SurviveIt/Interfaces/BreakableResource.h"

AToolItem::AToolItem()
{
    
}

bool AToolItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
    return InventoryHandler->AddToolToInventory(this) ? true : false;
}
