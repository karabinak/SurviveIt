
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "SurviveIt/Data/InventoryData.h"
//#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

class UInventoryWidget;
//class AToolItem;
//class AResourceItem;
class UBaseItem;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseItem* Item;

	FInventorySlot() : X(0), Y(0), Item(nullptr) {}

	FInventorySlot(int32 InX, int32 InY) : X(InX), Y(InY), Item(nullptr) {}

	bool operator == (const FInventorySlot & Other) const
	{
		return X == Other.X && Y == Other.Y;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UInventoryComponent : public UActorComponent, public IInventoryHandler
{
	GENERATED_BODY()

public:	
	UInventoryComponent();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 InventoryWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 InventoryHeight;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Initialize(int32 Width, int32 Height);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsValidPosition(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanItemFitAt(UBaseItem* Item, int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemAt(UBaseItem* Item, int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryStackItem(UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UBaseItem* RemoveItemAt(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UBaseItem* GetItemAt(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool MoveItem(int32 FromX, int32 FromY, int32 ToX, int32 ToY);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UBaseItem*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventorySlot> GetItemSlots(UBaseItem* Item) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearInventory();

protected:

	TArray<FInventorySlot> InventorySlots;

	virtual void BeginPlay() override;

	void InitializeGrid();

	bool AreItemSlotsEmpty(UBaseItem* Item, int32 StartX, int32 StartY) const;

	int32 GetSlotIndex(int32 X, int32 Y) const;

	void SetItemSlots(UBaseItem* Item, int32 StartX, int32 StartY);

	void ClearItemSlots(UBaseItem* Item);

	bool FindFirstFitPosition(UBaseItem* Item, int32& OutX, int32& OutY) const;

};