#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "SurviveIt/Data/ItemData.h"
//#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "BaseItem.generated.h"

//class UBoxComponent;
//class UImage;
class UInventoryComponent;
//class UItemWidget;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Tool UMETA(DisplayName = "Tool"),
	EIT_Resources UMETA(DisplayName = "Resources"),
	EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	EIT_Quest UMETA(DisplayName = "Quest"),

	EIT_MAX UMETA(DisplayName = "MAX")
};

UCLASS(BlueprintType)
class SURVIVEIT_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	FText Description;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	UStaticMesh* WorldMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	int32 MaxStackSize;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	int32 Width = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	int32 Height = 1;

	UItemData();

};

UCLASS(Blueprintable, BlueprintType)
class SURVIVEIT_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UBaseItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void Initialize(UItemData* InItemData, int32 InQuantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemData* GetItemData() const;

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetQuantity() const;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetQuantity(int32 NewQuantity);

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 AddQuantity(int32 AmountToAdd);

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 RemoveQuantity(int32 AmountToRemove);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool CanStackWith(UBaseItem* OtherItem) const;

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 TryStackWith(UBaseItem* OtherItem);

	UFUNCTION(BlueprintCallable, Category = "Item")
	UBaseItem* SplitStack(int32 SplitQuantity);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual bool Use(AActor* User);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool IsEmpty() const;

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool IsStackable() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FName, float> ItemProperties;

};
