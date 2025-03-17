// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatBarBase.generated.h"

class UVerticalBox;
class UBorder;
class UImage;
class UTextBlock;

/* 'Abstract' because we never want to actually make instance of it -
	only use it to create blueprint  */


UCLASS(Abstract)
class SURVIVEIT_API UStatBarBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, Category = "Controls", meta = (BindWidget))
	TObjectPtr<UBorder> MainBorder = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Controls", meta = (BindWidget))
	TObjectPtr<UImage> IconImage = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Controls", meta = (BindWidget))
	TObjectPtr<UBorder> PercentBar_Empty = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Controls", meta = (BindWidget))
	TObjectPtr<UBorder> PercentBar_Filled = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Controls", meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FLinearColor BarBackgroundColor = FLinearColor(0.3f, 0.f, 0.f, 0.3f);

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FLinearColor BarForegroundColor = FLinearColor(1.f, 0.f, 0.f, 0.75f);

	UPROPERTY(EditAnywhere, Category = "Stat Bar|Testing", meta = (ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1, Units = "Percent"))
	float CurrentPercentage = 0.f;

	UPROPERTY(EditAnywhere, Category = "Stat Bar|Testing", meta = (ClampMin = 0, UIMin = 0))
	int32 CurrentValue = 100.f;

	// no need for property
	FText CurrentValueText;

	void ProcessCurrentValueText();

	void UpdateWidget();
	
};
