#pragma once

#include "CoreMinimal.h"
#include "ResourceGeneratorData.generated.h"

//class AResourceItem;

UENUM(BlueprintType)
enum class EBiome : uint8
{
	EB_Plains UMETA(DisplayName = "Plains"),
	EB_Desert UMETA(DisplayName = "Desert"),
	EB_Tundra UMETA(DisplayName = "Tundra"),

	EB_MAX UMETA(DisplayName = "MAX")
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