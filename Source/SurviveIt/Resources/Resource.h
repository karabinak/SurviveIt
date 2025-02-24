// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Interfaces/BreakableResource.h"
#include "Resource.generated.h"

class UDataTable;

UCLASS()
class SURVIVEIT_API AResource : public AActor, public IBreakableResource
{
	GENERATED_BODY()
	
public:	
	AResource();

	virtual int32 GetRequiredHarvestLevel() const override { return RequiredHarvestLevel; }
	virtual EToolType GetRequiredToolType() const override { return RequiredToolType; }
	virtual void OnResourceDestroyed(AActor* BreakingActor) override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
	FName ResourceName = FName(TEXT("Stone"));

	UPROPERTY(EditAnywhere)
	UDataTable* ResourceDataTable;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ResourceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 Durability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EResourceType ResourceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 RequiredHarvestLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EToolType RequiredToolType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AResourceItem> ResourceDrop;

	UPROPERTY(EditAnywhere)
	int32 MinDrop;

	UPROPERTY(EditAnywhere)
	int32 MaxDrop;

public:	
	//virtual void Tick(float DeltaTime) override;


};
