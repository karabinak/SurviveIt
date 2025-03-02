// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldItem.h"

#include "Components/BoxComponent.h"
#include "SurviveIt/Items/BaseItem.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetCollisionProfileName(TEXT("Trigger"));

	Item = nullptr;
}

void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldItem::Initialize(UBaseItem* InItem)
{
	Item = InItem;
}

UBaseItem* AWorldItem::GetItem() const
{
	return Item;
}

void AWorldItem::SetItemQuantity(int32 NewQuantity)
{
	if (!Item) return;

	Item->SetQuantity(NewQuantity);

	if (Item->IsEmpty())
	{
		Destroy();
	}
}

UBaseItem* AWorldItem::OnPickup()
{
	UBaseItem* PickedUpItem = Item;
	Item = nullptr;

	Destroy();

	return PickedUpItem;
}

AWorldItem* AWorldItem::SpawnItemInWorld(UObject* WorldContextObject, UBaseItem* Item, FVector Location, FRotator Rotation)
{
	if (!WorldContextObject || !Item || Item->IsEmpty() || !Item->GetItemData()) return nullptr;
	
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AWorldItem* WorldItem = World->SpawnActor<AWorldItem>(AWorldItem::StaticClass(), Location, Rotation, SpawnParams);
	if (WorldItem)
	{
		WorldItem->Initialize(Item);
	}

	return WorldItem;
}
