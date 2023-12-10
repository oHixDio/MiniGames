// Fill out your copyright notice in the Description page of Project Settings.


#include "InitAnimText_UW.h"
#include <Components/TextBlock.h>

void UInitAnimText_UW::NativeConstruct()
{
	Super::NativeConstruct();
	InitAnimText->SetText(DefaultText);
}
