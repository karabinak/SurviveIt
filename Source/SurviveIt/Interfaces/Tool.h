
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurviveIt/Data/ItemData.h"
#include "Tool.generated.h"

UINTERFACE(MinimalAPI)
class UTool : public UInterface
{
	GENERATED_BODY()
};


class SURVIVEIT_API ITool
{
	GENERATED_BODY()

public:
	//UFUNCTION()
	//virtual int32 GetHarvestLevel() const = 0;
	//UFUNCTION()
	//virtual EToolType GetToolType() const = 0;
	//UFUNCTION()
	//virtual int32 GetHarvestDamage() const = 0;
};
