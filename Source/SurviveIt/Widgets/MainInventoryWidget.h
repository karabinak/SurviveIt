// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainInventoryWidget.generated.h"

class UCanvasPanel;
class UBorder;
//class UInventorySlotWidget;
class UHorizontalBox;
class UInventoryComponent;
class UInventoryGridWidget;

UCLASS()
class SURVIVEIT_API UMainInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeWidget(class UInventoryComponent* InInventoryComponent);


protected:

	UFUNCTION()
	void DelayedInitialize();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryGrid;

	UPROPERTY()
	TObjectPtr<UInventoryGridWidget> InventoryGridWidget = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UInventoryGridWidget> InventoryGridClass;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;


	/** Variables */

	//UPROPERTY(meta = (BindWidget))
	//UHorizontalBox* InventoryHorizontalBox;


//
//	UPROPERTY(meta = (BindWidget))
//	UCanvasPanel* MainInventorySection;
//
//	UPROPERTY(meta = (BindWidget))
//	UCanvasPanel* MainFunctionalSection;
//
//private:
//
//	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
