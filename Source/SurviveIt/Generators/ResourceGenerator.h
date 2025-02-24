// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Data/ResourceGeneratorData.h"
#include "ResourceGenerator.generated.h"

class AResource;

UCLASS()
class SURVIVEIT_API AResourceGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AResourceGenerator();

	//virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void SpawnResource();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	EBiome Biome = EBiome::EB_Desert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true", ClampMin = "1000.0", ClampMax = "100000.0"))
	float SpawnRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true", ClampMin = "0.01", ClampMax = "1.0"))
	float Density = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AResource> ResourceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TArray<AResource*> SpawnedResources;

	FTimerHandle SpawnResourceTimer;

	int32 MaxResources;

	//bool bSpawnResources = true;

public:	


};
