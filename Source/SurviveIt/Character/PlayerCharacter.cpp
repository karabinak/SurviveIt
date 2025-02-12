#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

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
	//DrawDebugLine(GetWorld(), Camera->GetComponentLocation(), EndLocation, FColor::Red);
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *HitResult.GetActor()->GetName());
	}
}