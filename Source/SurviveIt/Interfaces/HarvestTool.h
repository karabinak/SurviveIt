
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HarvestTool.generated.h"

UINTERFACE(MinimalAPI)
class UHarvestTool : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVEIT_API IHarvestTool
{
	GENERATED_BODY()

public:

	bool TestFunction();
};
