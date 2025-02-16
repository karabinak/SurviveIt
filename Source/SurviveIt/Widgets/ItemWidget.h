// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class AItemBase;
class UImage;
class UCanvasPanel;
class USizeBox;
class UBorder;
class UTextBlock;

UCLASS()
class SURVIVEIT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ItemCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	USizeBox* ItemSizeBox;

	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

public:

	void InitializeItemProperties(AItemBase* Item);

	void UpdateProperties(AItemBase* Item);

};
