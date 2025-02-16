// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "SurviveIt/Interfaces/BreakableResource.h"

AToolItem::AToolItem()
{
    ItemMesh->OnComponentHit.AddDynamic(this, &AToolItem::OnHit);
}

bool AToolItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
    return InventoryHandler->AddToolToInventory(this) ? true : false;
}

void AToolItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UBreakableResource::StaticClass()))
    {
        IBreakableResource* Breakable = Cast<IBreakableResource>(OtherActor);

        const bool bCanMine = 
            (GetHarvestLevel() >= Breakable->GetRequiredHarvestLevel()) && 
            (GetToolType() == Breakable->GetRequiredToolType());

        if (bCanMine)
        {
            Breakable->OnResourceDestroyed(GetOwner());
        }
    }
}
