// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "SurviveIt/Widgets/ItemWidget.h"

bool AResourceItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
	return (InventoryHandler->AddResourceToInventory(this)) ? true : false;
}

bool AResourceItem::CanAddQuantity(int32 Amount) const
{
	return (Quantity + Amount) <= MaxStack;
}

void AResourceItem::AddQuantity(int32 Amount)
{
	Quantity = FMath::Clamp(Quantity + Amount, 0, MaxStack);
	UpdateWidget();
}

void AResourceItem::UpdateWidget()
{
	if (!GetItemWidget()) return;
	GetItemWidget()->UpdateProperties(this);
}

void AResourceItem::Initialize(EResourceType Type, int32 StartQuantity, int32 NewStackMax, UTexture2D* NewItemIcon)
{
	ResourceType = Type;
	Quantity = StartQuantity;
	MaxStack = NewStackMax;
	ItemIcon = NewItemIcon;
}
