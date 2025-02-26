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
			Breakable->OnResourceHit(this, EquippedTool->GetHarvestDamage());
		}
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

void APlayerCharacter::OnDropPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDropPressed"));
	if (EquippedTool)
	{
		DropItemOnTheGround(EquippedTool);
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

void APlayerCharacter::DropItemOnTheGround(AItemBase* ItemToDrop)
{
	if (Inventory->IsItemInInventory(ItemToDrop))
	{	
		//EquippedTool->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedTool->SetActorEnableCollision(true);
		EquippedTool->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Template = EquippedTool;
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50.f;
		SpawnLocation.Z += 50.f;
		FVector Impulse = GetActorForwardVector() * 1000.f;
		AToolItem* Tool = GetWorld()->SpawnActor<AToolItem>(EquippedTool->GetClass(), SpawnLocation, GetActorRotation(), SpawnParameters);
		Tool->GetMesh()->AddImpulse(Impulse);

		EquippedTool->Destroy();
		bToolEquipped = false;
	}
}
