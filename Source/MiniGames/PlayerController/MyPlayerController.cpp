// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../HUD/MyHUD.h"
#include "../UserWidget/PauseMenu_UW.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h" // 追加
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加


// //////////////////// Engineで提供されているメソッドのoverride群 //////////////////// //

AMyPlayerController::AMyPlayerController()
	:Super()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayerController::RestartLevel()
{
	Super::RestartLevel();
}


// //////////////////// 頻度が高い処理をまとめたメソッド群 //////////////////// //

void AMyPlayerController::Setup(TObjectPtr<UInputComponent> MyInputComponent)
{

}

void AMyPlayerController::EnablePause()
{
	// PauseModeに変更
	SetPause(true);

	TObjectPtr<AMyHUD> HUD = GetHUD<AMyHUD>();
	// Pauseメニューの表示
	HUD->AddUI(HUD->GetPauseUI());
}

void AMyPlayerController::DisablePause()
{
	// PlayModeに変更
	SetPause(false);

	TObjectPtr<AMyHUD> HUD = GetHUD<AMyHUD>();
	// Pauseメニューの表示
	HUD->RemoveUI(HUD->GetPauseUI());
}


// //////////////////// InputActionにBindするメソッド群 //////////////////// //




