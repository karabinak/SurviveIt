// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Interfaces/Harvestable.h"
#include "ResourceNode.generated.h"

//class UDataTable;
class UBoxComponent;
class UParticleSystem;
class USoundBase;

USTRUCT(BlueprintType)
struct FHarvestDrop
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MinAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DropChance;

	FHarvestDrop() : ItemData(nullptr), MinAmount(1), MaxAmount(1), DropChance(1.f) {}
};

UCLASS()
class SURVIVEIT_API AResourceNode : public AActor, public IHarvestable
{
	GENERATED_BODY()
	
public:	
	AResourceNode();

	//virtual int32 GetRequiredHarvestLevel() const override { return RequiredHarvestLevel; }
	//virtual EToolType GetRequiredToolType() const override { return RequiredToolType; }
	//virtual void OnResourceHit(AActor* BreakingActor, int32 HarvestDamage) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystem* HarvestEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvesting")
	EToolType RequiredToolType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	TArray<FHarvestDrop> PossibleDrops;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	float RespawnTime;

	FTimerHandle RespawnTimerHandle;

	FTransform OriginalTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	UParticleSystem* HarvestParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvesting")
	USoundBase* HarvestSound;

	virtual void BeginPlay() override;

public:

	// IHarvestable interface
	virtual bool CanHarvest(EToolType ToolType) override;
	virtual TArray<UBaseItem*> Harvest(EToolType ToolType, float HarvestDamage) override;
	virtual EToolType GetRequiredToolType() override;


	UFUNCTION(BlueprintCallable, Category = "Harvesting")
	void Respawn();

	UFUNCTION(BlueprintCallable, Category = "Harvesting")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Harvesting")
	void PlayHarvestEffects();

	
	//UPROPERTY(BlueprintAssignable, Category = "Resource")
	//FOnNodeHarvested OnNodeHarvested;

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//bool TryHarvest(AActor* Harvester, UBaseItem* Tool);

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//bool IsValidTool(UBaseItem* Tool) const;

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//static EToolType GetToolTypeFromItem(UBaseItem* Item);

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//EResourceNodeType GetNodeType() const { return NodeType; }

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//EToolType GetRequiredToolType() const { return RequiredToolType; }

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//bool CanHarvest() const { return bCanHarvest; }

	//UFUNCTION(BlueprintCallable, Category = "Interaction")
	//void Highlight(bool bShouldHighlight);

protected:

	//UFUNCTION(BlueprintCallable, Category = "Resource")
	//void DropResources(int32 Amount, AActor* Harvester);

	//UFUNCTION()
	//void RespawnNode();

};
