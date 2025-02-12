
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Interfaces/HarvestTool.h"
#include "ItemBase.generated.h"

UCLASS()
class SURVIVEIT_API AItemBase : public AActor, public IHarvestTool
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


};
