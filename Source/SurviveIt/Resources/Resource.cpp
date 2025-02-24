// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

#include "SurviveIt/Data/DataTables.h"

AResource::AResource()
{
	PrimaryActorTick.bCanEverTick = false;

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(ResourceMesh);
}

void AResource::BeginPlay()
{
	Super::BeginPlay();

	/** Load Resource based on Biome From DataTable */
	if (ResourceDataTable)
	{
		static const FString ContextString(TEXT("Context"));
		FResourceData* ResourceData = ResourceDataTable->FindRow<FResourceData>(ResourceName, ContextString,  true);
		if (ResourceData)
		{
			ResourceMesh->SetStaticMesh(ResourceData->StaticMesh);
			Durability = ResourceData->Durability;
			ResourceType = ResourceData->ResourceType;
			RequiredHarvestLevel = ResourceData->RequiredHarvestLevel;
			RequiredToolType = ResourceData->RequiredToolType;
			ResourceDrop = ResourceData->ResourcesDrop;
			MinDrop = ResourceData->MinDrop;
			MaxDrop = ResourceData->MaxDrop;
		}
	}
}

void AResource::OnResourceDestroyed(AActor* BreakingActor)
{
	Destroy();
}