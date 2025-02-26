
#include "ItemBase.h"
#include "Components/BoxComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	//BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));

	SetRootComponent(ItemMesh);
	ItemMesh->SetupAttachment(GetRootComponent());

	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	//BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AItemBase::RemoveWidget()
{

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	ItemMesh->SetSimulatePhysics(true);
	//BoxComponent->SetSimulatePhysics(false);
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

