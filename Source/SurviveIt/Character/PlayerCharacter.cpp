#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

#include "SurviveIt/Components/Inventory.h"
#include "SurviveIt/Interfaces/Tool.h"
#include "SurviveIt/Interfaces/BreakableResource.h"
#include "SurviveIt/Widgets/InventoryWidget.h"
#include "SurviveIt/Items/ItemBase.h"
#include "SurviveIt/Items/ToolItem.h"
//#include "SurviveIt/Controller/SurvivalController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("InventoryComponent"));

	Camera->SetupAttachment(GetMesh(), FName(TEXT("head")));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	FVector EndLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * InteractionLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation(), EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Camera->GetComponentLocation(), EndLocation, FColor::Red);

	if (HitResult.GetActor())
	{
		HitActor = HitResult.GetActor();

		GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("ItemName: %s"), *HitActor->GetName()));
	}
	else
	{
		HitActor = nullptr;
		GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("ItemName: nullptr")));
	}
}

void APlayerCharacter::OnInteractionTriggered()
{
	if (HitActor != nullptr)
	{
		AItemBase* InventoryItem = Cast<AItemBase>(HitActor);
		if (!InventoryItem) return;

		InventoryItem->TryAddToInventory(Inventory);

		
		if (HitActor->GetClass()->ImplementsInterface(UTool::StaticClass()))
		{
			if (bToolEquipped) return;
			if (HitActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightWeaponSocket"))
			{
				HitActor->SetActorEnableCollision(false);
				EquippedTool = Cast<AToolItem>(HitActor);
				bToolEquipped = true;
				UE_LOG(LogTemp, Warning, TEXT("Attached"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("NotAttached"));
			}
		}
	}
}

bool APlayerCharacter::IsInventoryVisible()
{
	if (Inventory->IsInventoryWidgetVisible()) return true;
	return false;
}

void APlayerCharacter::OnLMBClicked()
{
	if (HitActor != nullptr && bToolEquipped)
	{
		if (HitActor->GetClass()->ImplementsInterface(UBreakableResource::StaticClass()))
		{
			IBreakableResource* Breakable = Cast<IBreakableResource>(HitActor);

			const bool bCanMine =
				(EquippedTool->GetHarvestLevel() >= Breakable->GetRequiredHarvestLevel()) &&
				(EquippedTool->GetToolType() == Breakable->GetRequiredToolType());

			if (bCanMine)
			{
				Breakable->OnResourceDestroyed(this);
			}
		}
	}
}
