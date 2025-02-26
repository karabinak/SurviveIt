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
	virtual void OnResourceHit(AActor* BreakingActor, int32 HarvestDamage) override;

protected:
	virtual void BeginPlay() override;
	

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	FName ResourceName = FName(TEXT(""));
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ResourceMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 Durability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EResourceType ResourceType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 RequiredHarvestLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EToolType RequiredToolType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AResourceItem> ResourceDrop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 MinDrop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 MaxDrop;

public:	
	//virtual void Tick(float DeltaTime) override;

	/*FORCEINLINE void SetResourceName(FName NewName) { ResourceName = NewName; }*/

};
