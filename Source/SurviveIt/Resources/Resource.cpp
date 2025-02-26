// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

#include "SurviveIt/Data/DataTables.h"
#include "SurviveIt/Items/ResourceItem.h"

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
	//if (ResourceDataTable)
	//{
	//	static const FString ContextString(TEXT("Context"));
	//	FResourceData* ResourceData = ResourceDataTable->FindRow<FResourceData>(ResourceName, ContextString,  true);
	//	if (ResourceData)
	//	{
	//		ResourceMesh->SetStaticMesh(ResourceData->StaticMesh);
	//		Durability = ResourceData->Durability;
	//		ResourceType = ResourceData->ResourceType;
	//		RequiredHarvestLevel = ResourceData->RequiredHarvestLevel;
	//		RequiredToolType = ResourceData->RequiredToolType;
	//		ResourceDrop = ResourceData->ResourcesDrop;
	//		MinDrop = ResourceData->MinDrop;
	//		MaxDrop = ResourceData->MaxDrop;
	//	}
	//}
}

void AResource::OnResourceHit(AActor* BreakingActor, int32 HarvestDamage)
{
	if (Durability - HarvestDamage > 0)
	{
		Durability -= HarvestDamage;
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, FString::Printf(TEXT("Durability of: %s is %i"), *GetName(), Durability));
		// Drop Items
	}
	else
	{
		int32 ResourceAmount = FMath::RandRange(MinDrop, MaxDrop);

		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 100.f;
		FVector Impulse = FVector(0.f, 0.f, 100.f);

		FActorSpawnParameters SpawnParameters;
		AResourceItem* ResourceItem = GetWorld()->SpawnActor<AResourceItem>(ResourceDrop, SpawnLocation, GetActorRotation(), SpawnParameters);
		ResourceItem->GetMesh()->AddImpulse(Impulse);

		int32 RemainingQuantity = ResourceAmount;
		const int32 MaxStack = ResourceItem->GetMaxStack();

		if (ResourceAmount <= MaxStack)
		{
			ResourceItem->SetResourceQuantity(ResourceAmount);
		}
		else
		{
			ResourceItem->SetResourceQuantity(MaxStack);
			RemainingQuantity -= MaxStack;

			while (RemainingQuantity > 0)
			{
				SpawnLocation = SpawnLocation + 50.f;
				int32 QuantityToAdd = FMath::Min(RemainingQuantity, MaxStack);
				RemainingQuantity -= QuantityToAdd;

				ResourceItem = GetWorld()->SpawnActor<AResourceItem>(ResourceDrop, SpawnLocation, GetActorRotation(), SpawnParameters);
				ResourceItem->SetResourceQuantity(QuantityToAdd);
				ResourceItem->GetMesh()->AddImpulse(Impulse);
				UE_LOG(LogTemp, Warning, TEXT("Spawned"));
			}
		}

		Destroy();
	}
}