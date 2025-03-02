#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

class UBaseItem;
class AResourceItem;

//UENUM(BlueprintType)
//enum class EItemType : uint8
//{
//	EIT_Tool UMETA(DisplayName = "Tool"),
//	EIT_Resources UMETA(DisplayName = "Resources"),
//	EIT_Consumable UMETA(DisplayName = "Consumable"),
//	EIT_Weapon UMETA(DisplayName = "Weapn"),
//	EIT_Quest UMETA(DisplayName = "Quest"),
//
//
//	EIT_MAX UMETA(DisplayName = "MAX")
//};



//UENUM(BlueprintType)
//enum class EToolType : uint8
//{
//	ETT_Axe UMETA(DisplayName = "Axe"),
//	ETT_Pickaxe UMETA(DisplayName = "Pickaxe"),
//
//	ETT_MAX UMETA(DisplayName = "MAX")
//};

UENUM(BlueprintType)
enum class EToolType : uint8
{
	ETT_None UMETA(DisplayName = "None"),
	ETT_Pickaxe UMETA(DisplayName = "Pickaxe"),
	ETT_Axe UMETA(DisplayName = "Axe"),
};

