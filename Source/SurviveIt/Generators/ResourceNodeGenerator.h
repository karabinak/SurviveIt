// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "SurviveIt/Data/ResourceGeneratorData.h"
#include "ResourceNodeGenerator.generated.h"

class AResourceNode;

USTRUCT(BlueprintType)
struct FResourceNodeTypeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	TSubclassOf<AResourceNode> NodeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	int32 MinNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	int32 MaxNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	float MinDistanceBetween;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	float Density;

	FResourceNodeTypeInfo() : NodeClass(nullptr), MinNodes(5), MaxNodes(10), MinDistanceBetween(500.f), Density(0.5f) {}
};

UCLASS()
class SURVIVEIT_API AResourceNodeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AResourceNodeGenerator();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	FVector GenerationExtent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	TArray<FResourceNodeTypeInfo> NodeTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Generation")
	TEnumAsByte<ECollisionChannel> PlacementTraceChannel;

	float MaxSlope;

	bool VisualizeGenerationArea;

	bool bGenerateOnBeginPlay;

	int32 GenerationSeed;

	TArray<AResourceNode*> GeneratedNodes;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:

	void GenerateResources();

	void ClearGeneratedResources();

	bool FindValidNodePosition(const FResourceNodeTypeInfo& NodeInfo, TArray<FVector>& ExistingPositions, FVector& OutPosition, FRotator& OutRotation);

	bool IsValidNodeLocation(const FVector& Location, float MinDistanceBetween, const TArray<FVector>& ExistingPositions);

	void RegenerateResources();

#if WITH_EDITOR

	virtual void DrawDebugHelpers();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif
};
