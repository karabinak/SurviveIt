// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarComponent.h"
#include "SurviveIt/Items/BaseItem.h"

UHotbarComponent::UHotbarComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	NumSlots = 5;
	SelectedSlot = 0;
}

void UHotbarComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UHotbarComponent::Initialize()
{
	HotbarItems.Empty();
	HotbarItems.SetNum(NumSlots);

	for (int32 i = 0; i < NumSlots; i++)
	{
		HotbarItems[i] = nullptr;
	}

	//APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//if (HUD)
	//{
	//	HUD->CreateInventoryWidget(this);
	//}
}

bool UHotbarComponent::SetItemInSlot(int32 SlotIndex, UBaseItem* Item)
{
	if (!IsValidSlotIndex(SlotIndex)) return false;
	
	HotbarItems[SlotIndex] = Item;
	OnHotbarSlotChanged.Broadcast(SlotIndex);

	return true;
}

UBaseItem* UHotbarComponent::GetItemFromSlot(int32 SlotIndex) const
{
	if (!IsValidSlotIndex(SlotIndex)) return nullptr;

	return HotbarItems[SlotIndex];
}

UBaseItem* UHotbarComponent::RemoveItemFromSlot(int32 SlotIndex)
{
	if (!IsValidSlotIndex(SlotIndex)) return nullptr;

	UBaseItem* RemovedItem = HotbarItems[SlotIndex];
	HotbarItems[SlotIndex] = nullptr;

	OnHotbarSlotChanged.Broadcast(SlotIndex);

	return RemovedItem;
}

void UHotbarComponent::SelectSlot(int32 SlotIndex)
{
	if (!IsValidSlotIndex(SlotIndex)) return;

	SelectedSlot = SlotIndex;
	OnHotbarSlotSelected.Broadcast(SelectedSlot);
}

UBaseItem* UHotbarComponent::GetSelectedItem() const
{
	return GetItemFromSlot(SelectedSlot);
}

bool UHotbarComponent::UseSelectedItem()
{
	UBaseItem* SelectedItem = GetSelectedItem();
	if (!SelectedItem) return false;

	AActor* Owner = GetOwner();
	if (!Owner) return false;

	bool bWasUsed = SelectedItem->Use(Owner);

	if (bWasUsed && SelectedItem->IsEmpty())
	{
		RemoveItemFromSlot(SelectedSlot);
	}
	else if (bWasUsed)
	{
		OnHotbarSlotChanged.Broadcast(SelectedSlot);
	}

	return bWasUsed;
}

bool UHotbarComponent::IsValidSlotIndex(int32 SlotIndex) const
{
	return SlotIndex >= 0 && SlotIndex < NumSlots;
}

void UHotbarComponent::ClearHotbar()
{
	for (int32 i = 0; i < NumSlots; i++)
	{
		HotbarItems[i] = nullptr;
		OnHotbarSlotChanged.Broadcast(i);
	}
}