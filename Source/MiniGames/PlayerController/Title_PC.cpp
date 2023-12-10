// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_PC.h"
#include "../HUD/Title_HUD.h"
#include "../UserWidget/Title_UW.h"
#include "InputAction.h" // 追加
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加


void ATitle_PC::BeginPlay()
{
	Super::BeginPlay();
	// InputMappingContextを設定
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
	// GameOnlyModeにする
	SetInputMode(FInputModeGameOnly());
	// マウスカーソルを消す
	bShowMouseCursor = false;

	GetWorldTimerManager().SetTimerForNextTick
	(
		[&]() {
			TObjectPtr<ATitle_HUD> HUD = GetHUD<ATitle_HUD>();
			HUD->AddUI(HUD->GetTitleUI());

			BindTitleAction();
		}
	);
}

void ATitle_PC::BindTitleAction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (UTitle_UW* TitleUI = Cast<UTitle_UW>(GetHUD<ATitle_HUD>()->GetTitleUI()))
		{
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, TitleUI, &UTitle_UW::OnButton));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, TitleUI, &UTitle_UW::OnSelect));
		}
	}
}