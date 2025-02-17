// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Interfaces/BreakableResource.h"
#include "Harvestable.generated.h"

UCLASS()
class SURVIVEIT_API AHarvestable : public AActor, public IBreakableResource
{
	GENERATED_BODY()
	
public:	
	AHarvestable();

	virtual int32 GetRequiredHarvestLevel() const override { return RequiredHarvestLevel; }
	virtual EToolType GetRequiredToolType() const override { return RequiredToolType; }
	virtual void OnResourceDestroyed(AActor* BreakingActor) override;

protected:
	virtual void BeginPlay() override;


private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HarvestableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EResourceType ResourceType = EResourceType::ERT_Wood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 RequiredHarvestLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EToolType RequiredToolType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AResourceItem> ResourceDrop;

public:	
	//virtual void Tick(float DeltaTime) override;


};
