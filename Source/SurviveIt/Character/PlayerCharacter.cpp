#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

#include "SurviveIt/Components/Inventory.h"
#include "SurviveIt/Interfaces/Tool.h"
#include "SurviveIt/Widgets/InventoryWidget.h"
#include "SurviveIt/Items/ItemBase.h"

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
	FVector EndLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * 500.f;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation(), EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Camera->GetComponentLocation(), EndLocation, FColor::Red);

	if (HitResult.GetActor() && Cast<AItemBase>(HitResult.GetActor()))
	{
		HitActor = HitResult.GetActor();

		GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("HarvestLevel: %s"), *HitActor->GetName()));
		//if (ITool* Tool = Cast<ITool>(HitResult.GetActor()))
		//{
		//	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("HarvestLevel: %i"), Tool->GetHarvestLevel()));
		//}
	}
	else
	{
		HitActor = nullptr;
		GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("HarvestLevel: nullptr")));
	}
}

void APlayerCharacter::OnInteractionTriggered()
{
	if (HitActor)
	{
		Inventory->AddToInventory(Cast<AItemBase>(HitActor));

		//AItemBase* Item = Cast<AItemBase>(HitActor);
		//if (!Item) return;

		//if (Inventory->AddToInventory(Item->GetItemWidth(), Item->GetItemHeight(), Item))
		//{
		//	//Item->Destroy();
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("NotAdded"));
		//}

		//if (HitActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightWeaponSocket"))
		//{
		//	HitActor->SetActorEnableCollision(false);
		//	UE_LOG(LogTemp, Warning, TEXT("Attached"));
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("NotAttached"));
		//}
	}
}

void APlayerCharacter::OnInventoryTriggered()
{
	//if (bInventoryOnScreen)
	//{
	//	InventoryWidget->RemoveFromParent();
	//	bInventoryOnScreen = false;
	//}
	//else
	//{
	//	bInventoryOnScreen = true;
	//	if (InventoryWidgetClass)
	//	{
	//		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	//		InventoryWidget->AddToViewport();
	//	}
	//}
}
