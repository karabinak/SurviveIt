// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BreakableResource.generated.h"

UINTERFACE(MinimalAPI)
class UBreakableResource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVEIT_API IBreakableResource
{
	GENERATED_BODY()

public:

	bool TestFunction();
};
