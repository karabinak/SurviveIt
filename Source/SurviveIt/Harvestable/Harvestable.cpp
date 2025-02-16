// Fill out your copyright notice in the Description page of Project Settings.


#include "Harvestable.h"

AHarvestable::AHarvestable()
{
	PrimaryActorTick.bCanEverTick = false;

	HarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(HarvestableMesh);
}

void AHarvestable::BeginPlay()
{
	Super::BeginPlay();
}


void AHarvestable::OnResourceDestroyed(AActor* BreakingActor)
{
	Destroy();
}