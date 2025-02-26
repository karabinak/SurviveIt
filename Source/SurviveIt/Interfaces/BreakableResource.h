// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurviveIt/Data/ItemData.h"
#include "BreakableResource.generated.h"

UINTERFACE(MinimalAPI)
class UBreakableResource : public UInterface
{
	GENERATED_BODY()
};


class SURVIVEIT_API IBreakableResource
{
	GENERATED_BODY()

public:

	virtual int32 GetRequiredHarvestLevel() const = 0;
	virtual EToolType GetRequiredToolType() const = 0;
	virtual void OnResourceHit(AActor* BreakingActor, int32 HarvestDamage) = 0;
};
