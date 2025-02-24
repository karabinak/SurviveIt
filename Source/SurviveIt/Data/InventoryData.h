#pragma once

#include "CoreMinimal.h"
#include "InventoryData.generated.h"

class AResourceItem;
class AItemBase;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItemBase* Item;
};

USTRUCT()
struct FResourceItemArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<AResourceItem>> Items;
};