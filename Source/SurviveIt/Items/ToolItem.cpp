// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolItem.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "SurviveIt/Interfaces/BreakableResource.h"

bool AToolItem::TryAddToInventory(IInventoryHandler* InventoryHandler)
{
    return InventoryHandler->AddToolToInventory(this) ? true : false;
}

void AToolItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->Implements<IBreakableResource>())
    {
        IBreakableResource* Breakable = Cast<IBreakableResource>(OtherActor);
        ITool* Tool = Cast<ITool>(GetOwner());

        const bool bCanMine = 
            (Tool->GetHarvestLevel() >= Breakable->GetRequiredHarvestLevel()) && 
            (Tool->GetToolType() == Breakable->GetRequiredToolType());

        if (bCanMine)
        {
            Breakable->OnResourceDestroyed(this);
        }
    }
}
