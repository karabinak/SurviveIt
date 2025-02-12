
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Interfaces/Tool.h"
#include "ItemBase.generated.h"


//class UStaticMeshComponent;

UCLASS()
class SURVIVEIT_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;


public:	



};
