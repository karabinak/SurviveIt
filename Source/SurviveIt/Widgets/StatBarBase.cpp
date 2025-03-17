// Fill out your copyright notice in the Description page of Project Settings.


#include "StatBarBase.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "SurviveIt/Helpers/CustomLogging.h"



void UStatBarBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(CLog, Warning, TEXT("NativeOnInitialized()"));
	UpdateWidget();
}

void UStatBarBase::ProcessCurrentValueText()
{
	CurrentValueText = FText::FromString(FString::FromInt(CurrentValue));
}

void UStatBarBase::UpdateWidget()
{
	if (!PercentBar_Filled || !PercentBar_Empty) return;

	FSlateChildSize EmptySize = FSlateChildSize(ESlateSizeRule::Fill);
	EmptySize.Value = 1.f - CurrentPercentage;

	FSlateChildSize FilledSize = FSlateChildSize(ESlateSizeRule::Fill);
	FilledSize.Value = CurrentPercentage;

	if (UHorizontalBoxSlot* FilledSlot = Cast<UHorizontalBoxSlot>(PercentBar_Filled->Slot))
		FilledSlot->SetSize(FilledSize);

	if (UHorizontalBoxSlot* EmptySlot = Cast<UHorizontalBoxSlot>(PercentBar_Empty->Slot))
		EmptySlot->SetSize(EmptySize);

	MainBorder->SetBrushColor(BarBackgroundColor);
	PercentBar_Filled->SetBrushColor(BarForegroundColor);
	IconImage->SetBrush(IconBrush);

	ProcessCurrentValueText();

	ValueText->SetText(CurrentValueText);
}

#if WITH_EDITOR

void UStatBarBase::OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue)
{
	if (MaxValue == 0.f) MaxValue = KINDA_SMALL_NUMBER;

	CurrentPercentage = FMath::Clamp(NewValue / MaxValue, 0.f, 1.f);
	CurrentValue = NewValue;
	UpdateWidget();
}

void UStatBarBase::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
	Super::OnDesignerChanged(EventArgs);
	// Update the widget, after editor changes due to layout. Resizing widget, or parent container
	UpdateWidget();
}

void UStatBarBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// Update after properties have been changed.

	const FString PropertyName = ((PropertyChangedEvent.Property != nullptr)
									? PropertyChangedEvent.Property->GetFName()
									: NAME_None).ToString();

	if (PropertyName == TEXT("CurrentPercentage") || PropertyName == TEXT("CurrentValue"))
	{
		UpdateWidget();
	}
}

#endif