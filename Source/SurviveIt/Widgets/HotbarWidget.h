// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotbarWidget.generated.h"

class UHotbarComponent;
class UHorizontalBox;

UCLASS()
class SURVIVEIT_API UHotbarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Hotbar")
	void InitializeWidget(UHotbarComponent* InHotbarComponent);

	UFUNCTION(BlueprintCallable, Category = "Hotbar")
	void RefreshHotbar();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hotbar")
	UHotbarComponent* HotbarComponent;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HotbarBox;

	UPROPERTY(EditDefaultsOnly, Category = "Hotbar")
	TSubclassOf<UUserWidget> HotbarSlotWidgetClass;

	UFUNCTION()
	void OnHotbarSlotChanged(int32 SlotIndex);

	UFUNCTION()
	void OnHotbarSlotSelected(int32 SlotIndex);
};
