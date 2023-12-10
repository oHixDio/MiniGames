// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_HUD.h"
#include "Blueprint/UserWidget.h"

void ATitle_HUD::BeginPlay()
{
	Super::BeginPlay();
	Setup();
}

void ATitle_HUD::Setup()
{
	Super::Setup();
	TitleUI = CreateUI(TitleUIClass);
}
