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

UCLASS()
class SURVIVEIT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ItemCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	USizeBox* ItemSizeBox;

	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

public:

	void InitializeItemProperties(AItemBase* Item);

};
