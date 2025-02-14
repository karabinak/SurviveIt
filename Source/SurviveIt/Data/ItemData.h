#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

class AItemBase;
class AResourceItem;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Tool UMETA(DisplayName = "Tool"),
	EIT_Resources UMETA(DisplayName = "Resources"),
	EIT_Consumable UMETA(DisplayName = "Consumable"),


	EIT_MAX UMETA(DisplayName = "MAX")
};

//UENUM(BlueprintType)
//enum class EHarvestLevel : uint8
//{
//	EHL_Wooden UMETA(DisplayName = "Wooden"),
//	EHL_Stone UMETA(DisplayName = "Stone"),
//	EHL_Iron UMETA(DisplayName = "Iron"),
//
//	EHL_MAX UMETA(DisplayName = "MAX")
//};

UENUM(BlueprintType)
enum class EToolType : uint8
{
	ETT_Axe UMETA(DisplayName = "Axe"),
	ETT_Pickaxe UMETA(DisplayName = "Pickaxe"),

	ETT_MAX UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	ERT_Wood UMETA(DisplayName = "Wood"),
	ERT_Stone UMETA(DisplayName = "Stone"),

	ERT_MAX UMETA(DisplayName = "MAX")
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItemBase* Item;
};

USTRUCT()
struct FResourceItemArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<AResourceItem>> Items;
};