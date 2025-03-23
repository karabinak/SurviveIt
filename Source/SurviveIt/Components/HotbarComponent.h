// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HotbarComponent.generated.h"

class UBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHotbarSlotChanged, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHotbarSlotSelected, int32, SlotIndex);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UBaseItem*, Item);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemMoved, UBaseItem*, Item, FIntPoint, MoveDimension);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UHotbarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHotbarComponent();

	/** DELEGATES */

	//UPROPERTY(BlueprintAssignable, Category = "Inventory")
	//FOnItemRemoved OnItemRemoved;

	//UPROPERTY(BlueprintAssignable, Category = "Inventory")
	//FOnItemMoved OnItemMoved;

	/** DELEGATES */


	int32 NumSlots;

	int32 SelectedSlot;

	FOnHotbarSlotChanged OnHotbarSlotChanged;

	FOnHotbarSlotSelected OnHotbarSlotSelected;

	void Initialize();

	bool SetItemInSlot(int32 SlotIndex, UBaseItem* Item);

	UBaseItem* GetItemFromSlot(int32 SlotIndex) const;

	UBaseItem* RemoveItemFromSlot(int32 SlotIndex);

	void SelectSlot(int32 SlotIndex);

	UBaseItem* GetSelectedItem() const;

	bool UseSelectedItem();

	bool IsValidSlotIndex(int32 SlotIndex) const;

	void ClearHotbar();

	UFUNCTION()
	bool SwapHotbarSlots(int32 SourceSlot, int32 TargetSlot);

protected:
	UPROPERTY()
	TArray<UBaseItem*> HotbarItems;

	//void InitializeSlots();

private:
	virtual void BeginPlay() override;
		
};
