// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceGenerator.h"

#include "SurviveIt/Resources/ResourceNode.h"

AResourceGenerator::AResourceGenerator()
{
	PrimaryActorTick.bCanEverTick = false;


}

void AResourceGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	//MaxResources = FMath::RoundToInt(SpawnRadius / 1000.f * Density);

	//GetWorld()->GetTimerManager().SetTimer(SpawnResourceTimer, this, &AResourceGenerator::SpawnResource, 5.f, true);
}

void AResourceGenerator::SpawnResource()
{
	//if (MaxResources <= 0)
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(SpawnResourceTimer);
	//	return;
	//}

	//FVector ActorLocation = GetActorLocation();
	//float HalfRadius = SpawnRadius / 2;
	//FVector ClampMinValue = ActorLocation - HalfRadius;
	//FVector ClampMaxValue = ActorLocation + HalfRadius;

	//float XRand = FMath::RandRange(ClampMinValue.X, ClampMaxValue.X);
	//float YRand = FMath::RandRange(ClampMinValue.Y, ClampMaxValue.Y);

	//FVector RandomSpawn = FVector(XRand, YRand, ActorLocation.Z);
	//FRotator RandomRot = FRotator(0.f, FMath::RandRange(0.f, 359.f), 0.f);

	//// TODO: TraceLane to detect landscape location and then spawn resource

	//FActorSpawnParameters SpawnParameters;
	//SpawnParameters.Owner = this;
	//AResource* Resource = GetWorld()->SpawnActor<AResource>(ResourceClass, RandomSpawn, RandomRot, SpawnParameters);
	//SpawnedResources.Add(Resource);

	//MaxResources -= 1;
}
