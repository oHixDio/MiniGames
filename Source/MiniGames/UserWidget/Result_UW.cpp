// Fill out your copyright notice in the Description page of Project Settings.


#include "Result_UW.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "Sound/SoundBase.h"
#include <MiniGames/HUD/MyHUD.h>
#include <Kismet/GameplayStatics.h>
#include <MiniGames/GameModeBase/HitAndBlow_GMB.h>

void UResult_UW::NativeConstruct()
{
	Super::NativeConstruct();

	Select = ESelect::RESTART;
	FTimerHandle InitHandle;
	GetOwningPlayer()->GetWorldTimerManager().SetTimer
	(
		InitHandle,
		[&]()
		{
			SetColorButton();
		},
		3,
		false
	);
}

void UResult_UW::OnButton()
{
	if (bIsDone) { return; }
	GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>()->ClearMyTimer();
	FTimerHandle ResultDoneHandle;
	GetOwningPlayer()->GetWorldTimerManager().SetTimer
	(
		ResultDoneHandle,
		[&]()
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			switch (Select)
			{
			case ESelect::RESTART:
				Controller->RestartLevel();
				break;
			case ESelect::BACK_TO_TITLE:
				UGameplayStatics::OpenLevel(GetWorld(), "Title");
				break;
			default:
				break;
			}
		},
		DoneRate,
		false
	);

	bIsDone = true;
	UGameplayStatics::SpawnSound2D(GetWorld(), DoneSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UResult_UW::OnSelect(const FInputActionValue& Value)
{
	if (bIsDone) { return; }
	float num = Value.Get<float>();
	if (ESelect::RESTART == Select)
	{
		Select = ESelect::BACK_TO_TITLE;
	}
	else
	{
		Select = ESelect::RESTART;
	}

	SetColorButton();
	UGameplayStatics::SpawnSound2D(GetWorld(), SelectSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UResult_UW::ResetColorToButton()
{
	RestartButton->SetBackgroundColor(White);
	BackToTitleButton->SetBackgroundColor(White);
}

void UResult_UW::SetColorButton()
{
	// ”’‚É–ß‚·
	ResetColorToButton();

	// ‘ÎÛ‚ð—Î‚É‚·‚é
	switch (Select)
	{
	case ESelect::RESTART:
		RestartButton->SetBackgroundColor(Green);
		break;
	case ESelect::BACK_TO_TITLE:
		BackToTitleButton->SetBackgroundColor(Green);
		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), Select);
}

void UResult_UW::SetResultText(bool bIsClear)
{
	const FString ClearText = TEXT("Game Clear!!");
	const FString FailedText = TEXT("Game Failed...");
	if (bIsClear)
	{
		DetailText->SetText(FText::FromString(ClearText));
		DetailText->SetColorAndOpacity(Green);
	}
	else
	{
		DetailText->SetText(FText::FromString(FailedText));
		DetailText->SetColorAndOpacity(Red);
	}
}
