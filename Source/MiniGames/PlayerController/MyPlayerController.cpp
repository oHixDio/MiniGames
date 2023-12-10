// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../HUD/MyHUD.h"
#include "../UserWidget/PauseMenu_UW.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h" // �ǉ�
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // �ǉ�
#include "EnhancedInputSubsystems.h" // �ǉ�


// //////////////////// Engine�Œ񋟂���Ă��郁�\�b�h��override�Q //////////////////// //

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


// //////////////////// �p�x�������������܂Ƃ߂����\�b�h�Q //////////////////// //

void AMyPlayerController::Setup(TObjectPtr<UInputComponent> MyInputComponent)
{

}

void AMyPlayerController::EnablePause()
{
	// PauseMode�ɕύX
	SetPause(true);

	TObjectPtr<AMyHUD> HUD = GetHUD<AMyHUD>();
	// Pause���j���[�̕\��
	HUD->AddUI(HUD->GetPauseUI());
}

void AMyPlayerController::DisablePause()
{
	// PlayMode�ɕύX
	SetPause(false);

	TObjectPtr<AMyHUD> HUD = GetHUD<AMyHUD>();
	// Pause���j���[�̕\��
	HUD->RemoveUI(HUD->GetPauseUI());
}


// //////////////////// InputAction��Bind���郁�\�b�h�Q //////////////////// //




