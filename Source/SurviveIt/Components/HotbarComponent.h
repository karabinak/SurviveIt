// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HotbarComponent.generated.h"

class UBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHotbarSlotChanged, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHotbarSlotSelected, int32, SlotIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UHotbarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHotbarComponent();

	int32 NumSlots;

	int32 SelectedSlot;

	FOnHotbarSlotChanged OnHotbarSlotChanged;

	FOnHotbarSlotSelected OnHotbarSlotSelected;

	void Initialize(int32 InNumSlots);

	bool SetItemInSlot(int32 SlotIndex, UBaseItem* Item);

	UBaseItem* GetItemFromSlot(int32 SlotIndex) const;

	UBaseItem* RemoveItemFromSlot(int32 SlotIndex);

	void SelectSlot(int32 SlotIndex);

	UBaseItem* GetSelectedItem() const;

	bool UseSelectedItem();

	bool IsValidSlotIndex(int32 SlotIndex) const;

	void ClearHotbar();

protected:
	UPROPERTY()
	TArray<UBaseItem*> HotbarItems;

	void InitializeSlots();

private:
	virtual void BeginPlay() override;
		
};
