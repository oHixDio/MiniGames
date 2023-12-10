// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_UW.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "../GameModeBase/Title_GMB.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"

void UTitle_UW::NativeConstruct()
{
	Super::NativeConstruct();

	


	Select = ESelect::HIT_AND_BLOW;
	SetColorButton();
}

UTitle_UW::UTitle_UW()
{
	//static constructorhelpers::fobjectfinder< usoundbase > find_sound(text("soundwave'/game/sound/se_ok.se_ok'"));
	//if (find_sound.succeeded()) {
	//	sound_obj = find_sound.object;
	//}
}

void UTitle_UW::OnButton()
{
	if (bIsDone) { return; }
	FTimerHandle DoneHandle;
	switch (Select)
	{
	case UTitle_UW::ESelect::HIT_AND_BLOW:
		GetOwningPlayer()->GetWorldTimerManager().SetTimer
		(
			DoneHandle,
			[&]()
			{
				UGameplayStatics::OpenLevel(GetWorld(), "HitAndBlow");
			},
			DoneRate,
			false
		);
		break;
	case UTitle_UW::ESelect::SLIDE_PUZZLE:
		GetOwningPlayer()->GetWorldTimerManager().SetTimer
		(
			DoneHandle,
			[&]()
			{
				UGameplayStatics::OpenLevel(GetWorld(), "SlidePuzzle");
			},
			DoneRate,
			false
		);
		break;
	case UTitle_UW::ESelect::QUIT:
		GetOwningPlayer()->GetWorldTimerManager().SetTimer
		(
			DoneHandle,
			[&]()
			{
				GetWorld()->GetAuthGameMode<AMiniGamesGameModeBase>()->QuitGame();
			},
			DoneRate,
			false
		);
		break;
	default:
		break;
	}
	bIsDone = true;
	UGameplayStatics::SpawnSound2D(GetWorld(), DoneSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UTitle_UW::OnSelect(const FInputActionValue& Value)
{
	if (bIsDone) { return; }

	float num = Value.Get<float>();
	switch (Select)
	{
	case UTitle_UW::ESelect::HIT_AND_BLOW:
		Select = num > 0 ? ESelect::SLIDE_PUZZLE : ESelect::QUIT;
		break;
	case UTitle_UW::ESelect::SLIDE_PUZZLE:
		Select = num > 0 ? ESelect::QUIT : ESelect::HIT_AND_BLOW;
		break;
	case UTitle_UW::ESelect::QUIT:
		Select = num > 0 ? ESelect::HIT_AND_BLOW : ESelect::SLIDE_PUZZLE;
		break;
	default:
		break;
	}
	SetColorButton();
	UGameplayStatics::SpawnSound2D(GetWorld(), SelectSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void UTitle_UW::OnCancel()
{
}

void UTitle_UW::ResetColorToButton()
{
	HitAndBlowButton->SetBackgroundColor(White);
	SlidePuzzleButton->SetBackgroundColor(White);
	QuitButton->SetBackgroundColor(White);
}

void UTitle_UW::SetColorButton()
{
	// ”’‚É–ß‚·
	ResetColorToButton();

	// ‘ÎÛ‚ð—Î‚É‚·‚é
	switch (Select)
	{
	case ESelect::HIT_AND_BLOW:
		HitAndBlowButton->SetBackgroundColor(Green);
		break;
	case ESelect::SLIDE_PUZZLE:
		SlidePuzzleButton->SetBackgroundColor(Green);
		break;
	case ESelect::QUIT:
		QuitButton->SetBackgroundColor(Green);
		break;
	default:
		break;
	}
}
