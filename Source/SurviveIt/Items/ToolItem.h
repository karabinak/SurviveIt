// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "SurviveIt/Interfaces/Tool.h"
#include "ToolItem.generated.h"


UCLASS()
class SURVIVEIT_API AToolItem : public AItemBase, public ITool
{
	GENERATED_BODY()
public:


	virtual int32 GetHarvestLevel() const override { return HarvestLevel; }

	virtual EToolType GetToolType() const override { return ToolType; }

	virtual bool TryAddToInventory(IInventoryHandler* InventoryHandler) override;
private:

	//UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	//EHarvestLevel HarvestLevel = EHarvestLevel::EHL_Wooden;


	/** 0 - Wooden; 1 - Stone; 2 - Iron; ... */
	UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	int32 HarvestLevel = 0;

	UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	EToolType ToolType = EToolType::ETT_Axe;


};
