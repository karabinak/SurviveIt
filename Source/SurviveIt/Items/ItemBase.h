#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurviveIt/Data/ItemData.h"
#include "SurviveIt/Interfaces/InventoryHandler.h"
#include "ItemBase.generated.h"

class UBoxComponent;
class UImage;
class UInventory;
class UItemWidget;

UCLASS()
class SURVIVEIT_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();

	virtual void Tick(float DeltaTime) override;

	virtual bool TryAddToInventory(IInventoryHandler* InventoryHandler) { return false; }

	void RemoveWidget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

private:

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemType ItemType = EItemType::EIT_Tool;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	int32 ItemWidth = 1;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	int32 ItemHeight = 1;

	UPROPERTY(EditAnywhere, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UItemWidget* ItemWidget;


public:	

	FORCEINLINE int32 GetItemWidth() { return ItemWidth; }
	FORCEINLINE int32 GetItemHeight() { return ItemHeight; }

	FORCEINLINE UTexture2D* GetItemIcon() { return ItemIcon; }
	FORCEINLINE EItemType GetItemType() { return ItemType; }

	FORCEINLINE void SetItemWidget(UItemWidget* InItemWidget) { ItemWidget = InItemWidget; }
	FORCEINLINE UItemWidget* GetItemWidget() { return ItemWidget; }

	FORCEINLINE FText GetItemName() { return ItemName; }
	FORCEINLINE UStaticMeshComponent* GetMesh() { return ItemMesh; }

};
