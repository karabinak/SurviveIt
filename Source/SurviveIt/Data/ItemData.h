#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

class UBaseItem;
class AResourceItem;

UENUM(BlueprintType)
enum class EToolType : uint8
{
	ETT_None UMETA(DisplayName = "None"),
	ETT_Pickaxe UMETA(DisplayName = "Pickaxe"),
	ETT_Axe UMETA(DisplayName = "Axe"),
};

