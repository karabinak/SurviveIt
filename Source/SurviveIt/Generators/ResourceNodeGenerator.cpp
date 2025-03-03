// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceNodeGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "NavigationSystem.h"

#include "SurviveIt/Resources/ResourceNode.h"


AResourceNodeGenerator::AResourceNodeGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	GenerationExtent = FVector(5000.f, 5000.f, 1000.f);
	PlacementTraceChannel = ECC_Visibility;
	MaxSlope = 30.f;
	VisualizeGenerationArea = true;
	bGenerateOnBeginPlay = true;
	GenerationSeed = 12345;
}

void AResourceNodeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	if (bGenerateOnBeginPlay)
	{
		GenerateResources();

	}
}

void AResourceNodeGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	DrawDebugHelpers();
#endif
}

void AResourceNodeGenerator::GenerateResources()
{
	ClearGeneratedResources();

	FRandomStream RandomStream(GenerationSeed);

	for (const FResourceNodeTypeInfo& NodeInfo : NodeTypes)
	{
		if (!NodeInfo.NodeClass) continue;

		int32 NumToSpawn = RandomStream.RandRange(NodeInfo.MinNodes, NodeInfo.MaxNodes);
		TArray<FVector> PlacedPositions;

		for (int32 i = 0; i < NumToSpawn; i++)
		{
			FVector NodePosition;
			FRotator NodeRotation;

			if (FindValidNodePosition(NodeInfo, PlacedPositions, NodePosition, NodeRotation))
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AResourceNode* SpawnNode = GetWorld()->SpawnActor<AResourceNode>(NodeInfo.NodeClass, NodePosition, NodeRotation, SpawnParams);

				if (SpawnNode)
				{
					GeneratedNodes.Add(SpawnNode);
					PlacedPositions.Add(NodePosition);
				}
			}
		}
	}
}

void AResourceNodeGenerator::ClearGeneratedResources()
{
	for (AResourceNode* Node : GeneratedNodes)
	{
		if (Node)
		{
			Node->Destroy();
		}
	}

	GeneratedNodes.Empty();
}

bool AResourceNodeGenerator::FindValidNodePosition(const FResourceNodeTypeInfo& NodeInfo, TArray<FVector>& ExistingPositions, FVector& OutPosition, FRotator& OutRotation)
{
	FRandomStream RandomStream(GenerationSeed);

	int32 MaxAttempts = 50;
	FVector Origin = GetActorLocation();

	for (int32 Attempt = 0; Attempt < MaxAttempts; Attempt++)
	{
		float X, Y;

		if (RandomStream.GetFraction() < NodeInfo.Density)
		{
			// Implemented a normal distribution

			float U1 = RandomStream.GetFraction();
			float U2 = RandomStream.GetFraction();

			if (U1 < 0.0001f) U1 = 0.0001f; // Avoid log(0)

			float Z0 = FMath::Sqrt(-2.f * FMath::Loge(U1) * FMath::Cos(2.f * PI * U2));
			float Z1 = FMath::Sqrt(-2.f * FMath::Loge(U1) * FMath::Sin(2.f * PI * U2));

			X = Z0 * (GenerationExtent.X * 0.3f);
			Y = Z1 * (GenerationExtent.Y * 0.3f);
		}
		else
		{
			X = RandomStream.FRandRange(-GenerationExtent.X, GenerationExtent.X);
			Y = RandomStream.FRandRange(-GenerationExtent.Y, GenerationExtent.Y);
		}

		FVector TestPosition = Origin + FVector(X, Y, GenerationExtent.Z);

		FHitResult HitResult;
		FVector TraceEnd = TestPosition - FVector(0.f, 0.f, GenerationExtent.Z * 2.f);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TestPosition, TraceEnd, PlacementTraceChannel))
		{
			float SlopeAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(HitResult.Normal, FVector::UpVector)));

			if (SlopeAngle <= MaxSlope)
			{
				if (IsValidNodeLocation(HitResult.Location, NodeInfo.MinDistanceBetween, ExistingPositions))
				{
					OutPosition = HitResult.Location + HitResult.Normal * 10.f;

					FVector UpVector = HitResult.Normal;

					OutRotation = FRotationMatrix::MakeFromZ(UpVector).Rotator();

					OutRotation.Yaw += RandomStream.FRandRange(0.f, 360.f);

					/*

						ROTATION OF OBJECTS NEED TO BE WORK ON

					*/

					return true;
				}
			}
		}
	}

	return false;
}

bool AResourceNodeGenerator::IsValidNodeLocation(const FVector& Location, float MinDistanceBetween, const TArray<FVector>& ExistingPositions)
{
	for (const FVector& Pos : ExistingPositions)
	{
		float DistanceSquered = FVector::DistSquared(Location, Pos);
		if (DistanceSquered < FMath::Square(MinDistanceBetween))
		{
			return false;
		}
	}

	// Additional checks
	// - Check if Location is not inside another object ect.

	return true;
}

void AResourceNodeGenerator::RegenerateResources()
{
	GenerationSeed++;

	GenerateResources();
}

#if WITH_EDITOR

void AResourceNodeGenerator::DrawDebugHelpers()
{
	if (VisualizeGenerationArea)
	{
		DrawDebugBox(GetWorld(), GetActorLocation(), GenerationExtent, FColor::Green, false, -1.f, 0, 5.f);
	}
}

void AResourceNodeGenerator::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	DrawDebugHelpers();
}

#endif
