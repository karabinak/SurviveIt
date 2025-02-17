// Fill out your copyright notice in the Description page of Project Settings.


#include "Harvestable.h"

#include "SurviveIt/Data/DataTables.h"

AHarvestable::AHarvestable()
{
	PrimaryActorTick.bCanEverTick = false;

	HarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(HarvestableMesh);
}

void AHarvestable::BeginPlay()
{
	Super::BeginPlay();

	/** Load Harvestable based on Biome From DataTable */
	if (HarvestableDataTable)
	{
		static const FString ContextString(TEXT("Context"));
		FHarvestableData* HarvestableData = HarvestableDataTable->FindRow<FHarvestableData>(BiomeName, ContextString,  true);
		if (HarvestableData)
		{
			HarvestableMesh->SetStaticMesh(HarvestableData->StaticMesh);
			Durability = HarvestableData->Durability;
			ResourceType = HarvestableData->ResourceType;
			RequiredHarvestLevel = HarvestableData->RequiredHarvestLevel;
			RequiredToolType = HarvestableData->RequiredToolType;
			ResourceDrop = HarvestableData->ResourcesDrop;
			MinDrop = HarvestableData->MinDrop;
			MaxDrop = HarvestableData->MaxDrop;
		}
	}
}


void AHarvestable::OnResourceDestroyed(AActor* BreakingActor)
{
	Destroy();
}