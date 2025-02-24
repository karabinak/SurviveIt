// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UTextBlock;

UCLASS()
class SURVIVEIT_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateItemName(FText InItemName);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;
	
};
