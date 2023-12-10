// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlow_HUD.h"
#include "Blueprint/UserWidget.h"

AHitAndBlow_HUD::AHitAndBlow_HUD()
	:Super()
{
	
}

void AHitAndBlow_HUD::BeginPlay()
{
	Super::BeginPlay();
	Setup();
}

const UUserWidget* AHitAndBlow_HUD::GetStartUI() const
{
	return StartUI;
}

const UUserWidget* AHitAndBlow_HUD::GetDetailUI() const
{
	return DetailUI;
}
const TObjectPtr<UUserWidget> AHitAndBlow_HUD::GetResultUI() const
{
	return ResultUI;
}
/*
const UUserWidget* AHitAndBlow_HUD::GetWinUI() const
{
	return WinUI;
}

const UUserWidget* AHitAndBlow_HUD::GetLoseUI() const
{
	return LoseUI;
}
*/
void AHitAndBlow_HUD::Setup()
{
	Super::Setup();
	StartUI = CreateUI(StartUIClass);
	DetailUI = CreateUI(DetailUIClass);
	ResultUI = CreateUI(ResultUIClass);
	// WinUI = CreateUI(WinUIClass);
	// LoseUI = CreateUI(LoseUIClass);
}
