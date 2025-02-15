// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ResourceItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEIT_API AResourceItem : public AItemBase
{
	GENERATED_BODY()

public:

	virtual bool TryAddToInventory(IInventoryHandler* InventoryHandler) override;

	bool CanAddQuantity(int32 Amount) const;
	void AddQuantity(int32 Amount);

	void UpdateWidget();

	void Initialize(EResourceType Type, int32 StartQuantity, int32 NewStackMax, UTexture2D* NewItemIcon);

private:

	UPROPERTY(EditAnywhere, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	int32 MaxStack = 5;

	UPROPERTY(EditAnywhere, Category = "Resource Properties", meta = (AllowPrivateAccess = "true"))
	EResourceType ResourceType = EResourceType::ERT_Wood;
	
public:

	FORCEINLINE EResourceType GetResourceType() { return ResourceType; }
	FORCEINLINE int32 GetResourceQuantity() { return Quantity; }
	FORCEINLINE void SetResourceQuantity(int32 InQuantity) { Quantity = InQuantity; }
	FORCEINLINE int32 GetMaxStack() { return MaxStack; }

};
