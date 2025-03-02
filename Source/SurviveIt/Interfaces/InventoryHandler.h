// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryHandler.generated.h"

class AToolItem;
class AResourceItem;
class UBaseItem;

UINTERFACE(MinimalAPI)
class UInventoryHandler : public UInterface
{
	GENERATED_BODY()
};


class SURVIVEIT_API IInventoryHandler
{
	GENERATED_BODY()

public:

	//virtual bool AddToolToInventory(AToolItem* ToolItem) = 0;
	//virtual bool AddResourceToInventory(AResourceItem* ResourceItem) = 0;
};
