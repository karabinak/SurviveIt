// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "SurviveIt/Widgets/ItemWidget.h"

bool AResourceItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
	if (InventoryHandler->AddResourceToInventory(this))
	{
		return true;
	}
	return false;
}

bool AResourceItem::CanAddQuantity(int32 InQuantity)
{
	if (Quantity >= MaxStack)
	{
		return false;
	}
	return true;
}

int32 AResourceItem::AddQuantity(int32 InQuantity)
{
	if (Quantity + InQuantity <= MaxStack)
	{
		Quantity += InQuantity;
		return 0;
	}
	Quantity = MaxStack;
	if (GetItemWidget())
	{
		GetItemWidget()->UpdateProperties(this);
	}
	return Quantity + InQuantity - MaxStack;
}
