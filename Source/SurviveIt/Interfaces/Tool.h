
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Tool.generated.h"

UINTERFACE(MinimalAPI)
class UTool : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVEIT_API ITool
{
	GENERATED_BODY()

public:

	bool TestFunction();
};
