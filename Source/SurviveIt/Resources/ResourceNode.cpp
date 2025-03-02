// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceNode.h"

#include "Components/BoxComponent.h"

#include "SurviveIt/Items/WorldItem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

//#include "SurviveIt/Data/DataTables.h"
//#include "SurviveIt/Items/ResourceItem.h"

AResourceNode::AResourceNode()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	InteractionBox->SetCollisionProfileName(TEXT("Trigger"));


	//NodeType = EResourceNodeType::ERT_Stone;
	RequiredToolType = EToolType::ETT_Pickaxe;
	MaxHealth = 100.f;
	Health = MaxHealth;
	RespawnTime = 5.f;
}

void AResourceNode::BeginPlay()
{
	Super::BeginPlay();

	OriginalTransform = GetActorTransform();
}

bool AResourceNode::CanHarvest(EToolType ToolType)
{
	if (RequiredToolType == EToolType::ETT_None) return true;

	return ToolType == RequiredToolType;
}

TArray<UBaseItem*> AResourceNode::Harvest(EToolType ToolType, float HarvestDamage)
{
	TArray<UBaseItem*> HarvestedItems;

	if (!CanHarvest(ToolType)) return HarvestedItems;

	float Damage = FMath::Max(5.f, HarvestDamage);
	Health -= Damage;

	PlayHarvestEffects();

	if (Health <= 0.f)
	{
		for (const FHarvestDrop& Drop : PossibleDrops)
		{
			if (Drop.ItemData && FMath::FRand() <= Drop.DropChance)
			{
				int32 Amount = FMath::RandRange(Drop.MinAmount, Drop.MaxAmount);

				UBaseItem* NewItem = NewObject<UBaseItem>(this);
				NewItem->Initialize(Drop.ItemData, Amount);

				if (NewItem)
				{
					HarvestedItems.Add(NewItem);
				}
			}
		}
	}

	return HarvestedItems;
}

EToolType AResourceNode::GetRequiredToolType()
{
	return RequiredToolType;
}

void AResourceNode::Respawn()
{
	Health = MaxHealth;

	if (MeshComponent)
	{
		MeshComponent->SetVisibility(true);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	SetActorTransform(OriginalTransform);
}

float AResourceNode::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

void AResourceNode::PlayHarvestEffects()
{
	// Harvest Effects
}
