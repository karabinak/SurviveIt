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
#include "SurviveIt/Widgets/PlayerWidget.h"
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
	
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		PlayerWidget->AddToViewport();
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeWidgetItemName();
}

void APlayerCharacter::OnInteractionTriggered()
{
	FHitResult HitResult = TraceLine();

	if (AItemBase* InventoryItem = Cast<AItemBase>(HitResult.GetActor()))
	{
		InventoryItem->DisableComponentsSimulatePhysics();
		InventoryItem->TryAddToInventory(Inventory);

		if (InventoryItem->Implements<UTool>())
		{
			if (bToolEquipped) return;
			if (InventoryItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightWeaponSocket"))
			{
				InventoryItem->SetActorEnableCollision(false);
				EquippedTool = Cast<AToolItem>(InventoryItem);
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

void APlayerCharacter::OnAttackPressed()
{
	FHitResult HitResult = TraceLine();

	if (HitResult.GetActor() == nullptr || !bToolEquipped) return;
	if (HitResult.GetActor()->Implements<UBreakableResource>())
	{
		IBreakableResource* Breakable = Cast<IBreakableResource>(HitResult.GetActor());

		const bool bCanMine =
			(EquippedTool->GetHarvestLevel() >= Breakable->GetRequiredHarvestLevel()) &&
			(EquippedTool->GetToolType() == Breakable->GetRequiredToolType());


		if (bCanMine)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can Mine"));
			Breakable->OnResourceDestroyed(this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Implements"));
	}
}

void APlayerCharacter::ChangeWidgetItemName()
{
	FHitResult HitResult = TraceLine();

	FText WidgetItemName;
	if (AItemBase* Item = Cast<AItemBase>(HitResult.GetActor()))
	{
		WidgetItemName = Item->GetItemName();
	}
	else
	{
		WidgetItemName = FText::FromString("");
	}

	if (PlayerWidget)
	{
		PlayerWidget->UpdateItemName(WidgetItemName);
	}
}

FHitResult APlayerCharacter::TraceLine()
{
	FHitResult HitResult;
	FVector EndLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * InteractionLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation(), EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Camera->GetComponentLocation(), EndLocation, FColor::Red);
	return HitResult;
}
