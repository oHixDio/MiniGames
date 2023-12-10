// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlowAmount_UW.h"
#include <Components/TextBlock.h>

void UHitAndBlowAmount_UW::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHitAndBlowAmount_UW::SetAmount(int HitAmount, int BlowAmount)
{
	
	const FString HitText = FString::FromInt(HitAmount) + TEXT(" Hit!!");
	const FString BlowText = FString::FromInt(BlowAmount) + TEXT(" Blow!!");

	HitAmountText->SetText(FText::FromString(HitText));
	BlowAmountText->SetText(FText::FromString(BlowText));
}
