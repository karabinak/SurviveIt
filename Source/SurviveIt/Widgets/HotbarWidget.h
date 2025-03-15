// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotbarWidget.generated.h"

class UHotbarComponent;
class UBorder;
class UCanvasPanel;
class UInventorySlotWidget;

UCLASS()
class SURVIVEIT_API UHotbarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Hotbar")
	void InitializeWidget(UHotbarComponent* InHotbarComponent);

	//UFUNCTION(BlueprintCallable, Category = "Hotbar")
	//void RefreshHotbar();

	UFUNCTION(BlueprintCallable, Category = "Hotbar")
	void DelayedInitialize();

	UFUNCTION(BlueprintCallable, Category = "Hotbar")
	void ShowHotbar();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hotbar")
	UHotbarComponent* HotbarComponent;

	UPROPERTY(meta = (BindWidget))
	UBorder* HotbarBorder;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* HotbarCanvas;
	
	UPROPERTY()
	TMap<int32, UInventorySlotWidget*> HotbarWidgets;

	UPROPERTY(EditDefaultsOnly, Category = "Hotbar")
	TSubclassOf<UInventorySlotWidget> HotbarSlotItem;

	UPROPERTY()
	float TileSize = 10.f;

	void CreateEmptySlots();

	UFUNCTION()
	void OnHotbarSlotChanged(int32 SlotIndex);

	UFUNCTION()
	void OnHotbarSlotSelected(int32 SlotIndex);
};
