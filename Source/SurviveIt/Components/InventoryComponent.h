
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "SurviveIt/Data/InventoryData.h"
//#include "SurviveIt/Data/ItemData.h"
//#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "InventoryComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryCleared);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UBaseItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantityChanged, UBaseItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UBaseItem*, Item, FIntPoint, ItemDimension);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemMoved, UBaseItem*, Item, FIntPoint, MoveDimension);


class UInventoryWidget;
//class AToolItem;
//class AResourceItem;
class UBaseItem;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseItem* Item;

	FInventorySlot() : Column(0), Row(0), Item(nullptr) {}

	FInventorySlot(int32 InColumn, int32 InRow) : Column(InColumn), Row(InRow), Item(nullptr) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVEIT_API UInventoryComponent : public UActorComponent//, public IInventoryHandler
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	/** DELEGATES */

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemRemoved OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnQuantityChanged OnQuantityChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemMoved OnItemMoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryCleared OnInventoryCleared;

	/** DELEGATES */


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 InventoryWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 InventoryHeight;


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsValidPosition(int32 Column, int32 Row) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanItemFitAt(UBaseItem* Item, int32 Column, int32 Row) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemAt(UBaseItem* Item, int32 Column, int32 Row);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryStackItem(UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UBaseItem* RemoveItemAt(int32 Column, int32 Row);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UBaseItem* GetItemAt(int32 Column, int32 Row) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool MoveItem(int32 FromColumn, int32 FromRow, int32 ToColumn, int32 ToRow);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UBaseItem*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventorySlot> GetItemSlots(UBaseItem* Item) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearInventory();

protected:

	/*  WIDGETS  */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	//UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere)
	TArray<FInventorySlot> InventorySlots;

	virtual void BeginPlay() override;

	void Initialize();

	bool AreItemSlotsEmpty(UBaseItem* Item, int32 StartColumn, int32 StartRow) const;

	int32 GetSlotIndex(int32 Column, int32 Row) const;

	void SetItemSlots(UBaseItem* Item, int32 StartColumn, int32 StartRow);

	void ClearItemSlots(UBaseItem* Item);

	bool FindFirstFitPosition(UBaseItem* Item, int32& OutColumn, int32& OutRow) const;

};