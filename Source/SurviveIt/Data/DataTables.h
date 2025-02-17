#pragma once

#include "CoreMinimal.h"
#include "DataTables.generated.h"

USTRUCT(BlueprintType)
struct FHarvestableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredHarvestLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EToolType RequiredToolType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AResourceItem> ResourcesDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxDrop;
};