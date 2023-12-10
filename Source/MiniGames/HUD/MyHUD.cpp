// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
	:Super()
{
	
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	
}

const TObjectPtr<UUserWidget> AMyHUD::GetPauseUI() const
{
	return PauseUI;
}

const TObjectPtr<UUserWidget> AMyHUD::GetLoadingUI() const
{
	return LoadingUI;
}

void AMyHUD::Setup()
{
	PauseUI = CreateUI(PauseMenuUIClass);
	LoadingUI = CreateUI(LoadingUIClass);
}

TObjectPtr<class UUserWidget> AMyHUD::CreateUI(TSubclassOf<UUserWidget> WidgetClass)
{
	return CreateWidget(GetWorld(), WidgetClass);
}

void AMyHUD::AddUI(TObjectPtr<UUserWidget> Widget)
{
	// ì¬‚³‚ê‚½UI‚ð•\Ž¦
	Widget->AddToViewport();
}

void AMyHUD::RemoveUI(TObjectPtr<UUserWidget> Widget)
{
	Widget->RemoveFromParent();
}


