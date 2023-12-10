// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu_UW.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "Sound/SoundBase.h"
#include <MiniGames/HUD/MyHUD.h>
#include <Kismet/GameplayStatics.h>
#include <MiniGames/PlayerController/MyPlayerController.h>
#include <MiniGames/GameModeBase/HitAndBlow_GMB.h>

void UPauseMenu_UW::NativeConstruct()
{
	Super::NativeConstruct();
	Select = ESelect::RESUME;
	SetColorButton();
	UGameplayStatics::SpawnSound2D(GetWorld(), PauseSE, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UPauseMenu_UW::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bShuldCntTimer)
	{
		DoneTimer -= InDeltaTime;
	}
	if (DoneTimer < 0)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		switch (Select)
		{
		case UPauseMenu_UW::ESelect::RESUME:
			break;
		case UPauseMenu_UW::ESelect::RESTART:
			Controller->RestartLevel();
			DoneTimer = 1;
			bShuldCntTimer = false;
			break;
		case UPauseMenu_UW::ESelect::BACK_TO_TITLE:
			UGameplayStatics::OpenLevel(GetWorld(), "Title");
			DoneTimer = 1;
			bShuldCntTimer = false;
			break;
		default:
			break;
		}
	}
}

void UPauseMenu_UW::OnButton()
{
	if (bIsDone) { return; }

	switch (Select)
	{
	case ESelect::RESUME:
		OnCancel();
		break;
	case ESelect::RESTART: /* fall through*/
	case ESelect::BACK_TO_TITLE:
		GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>()->ClearMyTimer();
		bShuldCntTimer = true;
		bIsDone = true;
		break;
	default:
		break;
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), DoneSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UPauseMenu_UW::OnSelect(const FInputActionValue& Value)
{
	if (bIsDone) { return; }
	float num = Value.Get<float>();
	switch (Select)
	{
	case ESelect::RESUME:
		Select = num > 0 ? ESelect::RESTART : ESelect::BACK_TO_TITLE;
		break;
	case ESelect::RESTART:
		Select = num > 0 ? ESelect::BACK_TO_TITLE : ESelect::RESUME;
		break;
	case ESelect::BACK_TO_TITLE:
		Select = num > 0 ? ESelect::RESUME : ESelect::RESTART;
		break;
	default:
		break;
	}

	SetColorButton();
	UGameplayStatics::SpawnSound2D(GetWorld(), SelectSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UPauseMenu_UW::OnCancel()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Controller->DisablePause();
}

void UPauseMenu_UW::ResetColorToButton()
{
	ResumeButton->SetBackgroundColor(White);
	RestartButton->SetBackgroundColor(White);
	BackToTitleButton->SetBackgroundColor(White);
}

void UPauseMenu_UW::SetColorButton()
{
	// ”’‚É–ß‚·
	ResetColorToButton();

	// ‘ÎÛ‚ð—Î‚É‚·‚é
	switch (Select)
	{
	case ESelect::RESUME:
		ResumeButton->SetBackgroundColor(Green);
		break;
	case ESelect::RESTART:
		RestartButton->SetBackgroundColor(Green);
		break;
	case ESelect::BACK_TO_TITLE:
		BackToTitleButton->SetBackgroundColor(Green);
		break;
	default:
		break;
	}
}
