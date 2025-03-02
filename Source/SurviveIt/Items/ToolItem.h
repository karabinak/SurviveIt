// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
//#include "SurviveIt/Interfaces/Tool.h"
#include "SurviveIt/Data/ItemData.h"
#include "ToolItem.generated.h"

UCLASS(BlueprintType)
class SURVIVEIT_API UToolData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	EToolType ToolType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	float Durability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	float MaxDurability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	float HarvestingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tool Properties")
	TArray<TSubclassOf<AActor>> EffectiveAgainst;

	UToolData() : ToolType(EToolType::ETT_Pickaxe), Durability(100.f), HarvestingSpeed(1.f), Damage(10.f) {}
};

UCLASS()
class SURVIVEIT_API UToolItem : public UBaseItem//, public ITool
{
	GENERATED_BODY()

public:
	UToolItem();

	UFUNCTION(BlueprintCallable, Category = "Tool")
	void InitializeTool(UItemData* InItemData, UToolData* InToolData, float InCurrentDurability = -1.f);

	UFUNCTION(BlueprintCallable, Category = "Tool")
	UToolData* GetToolData() const;

	UFUNCTION(BlueprintCallable, Category = "Tool")
	float GetCurrentDurability() const;

	UFUNCTION(BlueprintCallable, Category = "Tool")
	void SetCurrentDurability(float NewDurability);

	UFUNCTION(BlueprintCallable, Category = "Tool")
	void ReduceDurability(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Tool")
	bool IsBroken() const;

	UFUNCTION(BlueprintCallable, Category = "Tool")
	bool Repair(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Tool")
	bool UseToolOn(AActor* Target);

	virtual bool Use(AActor* User) override;

private:

	UPROPERTY()
	UToolData* ToolData;

	UPROPERTY()
	float CurrentDurability;

	/** Interface Implementation */
	//virtual int32 GetHarvestLevel() const override { return HarvestLevel; }
	//virtual EToolType GetToolType() const override { return ToolType; }
	//virtual int32 GetHarvestDamage() const override { return HarvestDamage; }

	//virtual bool TryAddToInventory(IInventoryHandler* InventoryHandler) override;

protected:

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:

	/** 0 - Wooden; 1 - Stone; 2 - Iron; ... */
	//UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	//int32 HarvestLevel = 0;

	//UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	//int32 HarvestDamage = 10;

	//UPROPERTY(EditAnywhere, Category = "Tool Properties", meta = (AllowPrivateAccess = "true"))
	//EToolType ToolType = EToolType::ETT_Axe;


};
