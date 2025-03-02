// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Data/ItemData.h"
#include "Harvestable.generated.h"

class ABaseItem;

//UENUM(BlueprintType)
//enum class EToolType : uint8
//{
//	ETT_None UMETA(DisplayName = "None"),
//	ETT_Pickaxe UMETA(DisplayName = "Pickaxe"),
//	ETT_Axe UMETA(DisplayName = "Axe"),
//};

UINTERFACE(MinimalAPI)
class UHarvestable : public UInterface
{
	GENERATED_BODY()
};


class SURVIVEIT_API IHarvestable
{
	GENERATED_BODY()

public:

	UFUNCTION(Category = "Harvesting")
	virtual bool CanHarvest(EToolType ToolType) = 0;

	UFUNCTION(Category = "Harvesting")
	virtual TArray<UBaseItem*> Harvest(EToolType ToolType, float HarvestDamage) = 0;

	UFUNCTION(Category = "Harvesting")
	virtual EToolType GetRequiredToolType() = 0;

	//virtual int32 GetRequiredHarvestLevel() const = 0;
	//virtual EToolType GetRequiredToolType() const = 0;
	//virtual void OnResourceHit(AActor* BreakingActor, int32 HarvestDamage) = 0;
};
