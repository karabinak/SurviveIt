#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Blueprint/UserWidget.h"

#include "SurviveIt/Components/InventoryComponent.h"
#include "SurviveIt/Components/HotbarComponent.h"
//#include "SurviveIt/Interfaces/Tool.h"
#include "SurviveIt/Interfaces/Harvestable.h"
//#include "SurviveIt/Widgets/InventoryWidget.h"
#include "SurviveIt/Items/WorldItem.h"
#include "SurviveIt/Items/BaseItem.h"
#include "SurviveIt/Items/ToolItem.h"
//#include "SurviveIt/Widgets/PlayerWidget.h"
//#include "SurviveIt/Controller/SurvivalController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	HotbarComponent = CreateDefaultSubobject<UHotbarComponent>(TEXT("HotbarComponent"));

	Camera->SetupAttachment(GetMesh(), FName(TEXT("head")));

	InteractionDistance = 200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Inventory size
	InventoryComponent->Initialize(10, 5);

	HotbarComponent->Initialize(10);
	
	//if (PlayerWidgetClass)
	//{
	//	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
	//	PlayerWidget->AddToViewport();
	//}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ChangeWidgetItemName();
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

UHotbarComponent* APlayerCharacter::GetHotbarComponent() const
{
	return HotbarComponent;
}

void APlayerCharacter::ToggleInventory()
{
	/* TODO
	
		Create HUD
		HUD->ToggleInventoryUI();
	*/
}

bool APlayerCharacter::TryPickupItem()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * InteractionDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	// DEBUG LINE
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

	if (bHit)
    {
        AWorldItem* WorldItem = Cast<AWorldItem>(HitResult.GetActor());
        if (WorldItem)
        {
            UBaseItem* Item = WorldItem->GetItem();
            if (Item)
            {
                if (InventoryComponent->AddItem(Item))
                {
                    WorldItem->OnPickup();
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool APlayerCharacter::DropItemFromInventory(UBaseItem* Item, int32 Quantity)
{
	if (!Item ||  Quantity <= 0) return false;

	int32 CurrentQuantity = Item->GetQuantity();
	if (Quantity > CurrentQuantity)
	{
		Quantity = CurrentQuantity;
	}

	UBaseItem* DroppedItem = nullptr;

	if (Quantity < CurrentQuantity)
	{
		DroppedItem = Item->SplitStack(Quantity);
	}
	else
	{
		TArray<FInventorySlot> ItemSlots = InventoryComponent->GetItemSlots(Item);
		if (ItemSlots.Num() > 0)
		{
			DroppedItem = InventoryComponent->RemoveItemAt(ItemSlots[0].X, ItemSlots[0].Y);
		}
	}

	if (DroppedItem)
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AWorldItem::SpawnItemInWorld(GetWorld(), DroppedItem, SpawnLocation, SpawnRotation);
		return true;
	}
	return false;
}

void APlayerCharacter::UseHotbarItem()
{
	HotbarComponent->UseSelectedItem();
}

void APlayerCharacter::SelectHotbarSlot(int32 SlotIndex)
{
	HotbarComponent->SelectSlot(SlotIndex);
}

AActor* APlayerCharacter::GetLookAtActor(float MaxDistance)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * MaxDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		return HitResult.GetActor();
	}

	return nullptr;
}

bool APlayerCharacter::TryHarvest()
{
	AActor* LookAtActor = GetLookAtActor();
	if (!LookAtActor || !LookAtActor->Implements<UHarvestable>()) return false;


	UToolItem* EquippedTool = GetEquippedTool();
	EToolType ToolType = EquippedTool ? EquippedTool->GetToolData()->ToolType : EToolType::ETT_None;
	float HarvestDamage = EquippedTool ? EquippedTool->GetToolData()->Damage : 5.0f;

	IHarvestable* Harvestable = Cast<IHarvestable>(LookAtActor);
	if (Harvestable->CanHarvest(ToolType))
	{
		TArray<UBaseItem*> HarvestedItems = Harvestable->Harvest(ToolType, HarvestDamage);

		bool AllitemsCollected;
		for (UBaseItem* Item : HarvestedItems)
		{
			if (!InventoryComponent->AddItem(Item))
			{
				AWorldItem::SpawnItemInWorld(this, Item, GetActorLocation(), FRotator::ZeroRotator);
				AllitemsCollected = false;
			}
		}

		if (EquippedTool)
		{
			EquippedTool->ReduceDurability(1.f);
		}

		// Feedback to player that they harvest Item UI
		return true;
	}
	return false;
}

UToolItem* APlayerCharacter::GetEquippedTool()
{
	UBaseItem* SelectedItem = HotbarComponent->GetSelectedItem();

	return Cast<UToolItem>(SelectedItem);
}
