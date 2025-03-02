// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "SurviveIt/Character/PlayerCharacter.h"

UToolItem::UToolItem()
{
	ToolData = nullptr;
	CurrentDurability = 0.f;
}

void UToolItem::InitializeTool(UItemData* InItemData, UToolData* InToolData, float InCurrentDurability)
{
	Initialize(InItemData);

	ToolData = InToolData;

	if (ToolData)
	{
		CurrentDurability = (InCurrentDurability >= 0.f) ? InCurrentDurability : ToolData->Durability;
	}
	else
	{
		CurrentDurability = 0.f;
	}
}

UToolData* UToolItem::GetToolData() const
{
	return ToolData;
}

float UToolItem::GetCurrentDurability() const
{
	return CurrentDurability;
}

void UToolItem::SetCurrentDurability(float NewDurability)
{
	if (ToolData)
	{
		CurrentDurability = FMath::Clamp(NewDurability, 0.f, ToolData->Durability);
	}
	else
	{
		CurrentDurability = 0.f;
	}
}

void UToolItem::ReduceDurability(float Amount)
{
	CurrentDurability = FMath::Max(0.f, CurrentDurability - Amount);

	if (CurrentDurability <= 0.f)
	{
		IsBroken();
	}
}

bool UToolItem::IsBroken() const
{
	return CurrentDurability <= 0.f;
}

bool UToolItem::Repair(float Amount)
{
	if (Amount <= 0.f || !ToolData) return false;
	if (CurrentDurability >= ToolData->Durability) return false;

	CurrentDurability = FMath::Min(ToolData->Durability, CurrentDurability + Amount);
	return true;
}

bool UToolItem::UseToolOn(AActor* Target)
{
	if (!Target || IsBroken() || !ToolData) return false;

	bool bEffective = false;

	for (TSubclassOf<AActor> EffectiveClass : ToolData->EffectiveAgainst)
	{
		if (Target->IsA(EffectiveClass))
		{
			bEffective = true;
			break;
		}
	}

	float DurabilityReduction = bEffective ? 1.f : 2.f;
	ReduceDurability(DurabilityReduction);

	// TODO
	// Function on target for Resources Mining etc.

	return true;

}

bool UToolItem::Use(AActor* User)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(User);
	if (!Character) return false;
	
	// WORK ON

	return false;
}

//bool AToolItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
//{
//    return InventoryHandler->AddToolToInventory(this) ? true : false;
//}
