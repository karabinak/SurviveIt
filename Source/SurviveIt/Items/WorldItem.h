// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldItem.generated.h"

class UBaseItem;
class UBoxComponent;

UCLASS()
class SURVIVEIT_API AWorldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldItem();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Temoporal
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UBaseItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UBaseItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionBox;

	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	void Initialize(UBaseItem* InItem);

	UBaseItem* GetItem() const;

	void SetItemQuantity(int32 NewQuantity);

	UBaseItem* OnPickup();

	static AWorldItem* SpawnItemInWorld(UObject* WorldContextObject, UBaseItem* Item, FVector Location, FRotator Rotation);

	void UpdateItemVisuals();

};
