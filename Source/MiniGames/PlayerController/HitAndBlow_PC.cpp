// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlow_PC.h"
#include "../GameModeBase/HitAndBlow_GMB.h"
#include "../GameStateBase/HitAndBlow_GSB.h"
#include "../HUD/HitAndBlow_HUD.h"
#include "../Actor/Board_HnB.h"
#include "../UserWidget/PauseMenu_UW.h"
#include <MiniGames/UserWidget/Result_UW.h>
#include "InputAction.h" // 追加
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加
#include <Kismet/GameplayStatics.h>

AHitAndBlow_PC::AHitAndBlow_PC()
	:Super()
{
	
}

void AHitAndBlow_PC::BeginPlay()
{
	Super::BeginPlay();

	// InputMappingContextを設定
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
UE_LOG(LogTemp, Warning, TEXT("HitAndBlow_PC"));
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	/*
	Setup(InputComponent);

	// GameStateBase取得
	MyGameState = GetWorld()->GetGameState<AHitAndBlow_GSB>();

	// Board取得
	Board = Cast<ABoard_HnB>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard_HnB::StaticClass()));
	
	// kari
	Board->TurnInit(MyGameState->GetCurTurn());

	MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PLAY);
	*/
}

void AHitAndBlow_PC::BindPauseAction()
{
	// Pauseのみできる
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::EnablePause));
	}
}

void AHitAndBlow_PC::BindPauseModeAction()
{
	// Pause状態の操作
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::DisablePause));

		// PauseMenuの機能をバインド
		if (UPauseMenu_UW* PauseUI = Cast<UPauseMenu_UW>(GetHUD<AHitAndBlow_HUD>()->GetPauseUI()))
		{
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, PauseUI, &UPauseMenu_UW::OnButton));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToCancel, ETriggerEvent::Triggered, PauseUI, &UPauseMenu_UW::OnCancel));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, PauseUI, &UPauseMenu_UW::OnSelect));
		}
	}
}

void AHitAndBlow_PC::BindResultModeAction()
{
	// Result_UWから機能を選択
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		// PauseMenuの機能をバインド
		if (UResult_UW* ResultUI = Cast<UResult_UW>(GetHUD<AHitAndBlow_HUD>()->GetResultUI()))
		{
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, ResultUI, &UResult_UW::OnButton));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, ResultUI, &UResult_UW::OnSelect));
		}
	}
	
}

void AHitAndBlow_PC::BindPlayModeAction()
{
	// Play状態の操作
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::EnablePause));

		// Boardの機能をバインド
		AHitAndBlow_GMB* GameMode = GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>();
		if (ABoard_HnB* Board = Cast<ABoard_HnB>(GameMode->GetBoard()))
		{
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, GameMode, &AHitAndBlow_GMB::Interact));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectX, ETriggerEvent::Triggered, Board, &ABoard_HnB::TargetSelectPointUpdate));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, Board, &ABoard_HnB::TargetChoisePointUpdate));
		}
	}
}

void AHitAndBlow_PC::RemoveBindAction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind済みActionを取り外す
		for (FInputBindingHandle BindingAction : BindingActionList)
		{
			EnhancedInputComponent->RemoveBinding(BindingAction);
		}
	}
}

void AHitAndBlow_PC::AddBindAction(EHitAndBlowState State)
{
	switch (State)
	{
	case EHitAndBlowState::NONE:
		break;
	case EHitAndBlowState::BEFORE_PLAY:
		break;
	case EHitAndBlowState::PLAY:
		BindPlayModeAction();
		break;
	case EHitAndBlowState::AFTER_PLAY:
		break;
	case EHitAndBlowState::RESULT:
		BindResultModeAction();
		break;
	default:
		break;
	}
}

void AHitAndBlow_PC::SetPlayerEnableState(bool bIsEnable)
{
	if (bIsEnable)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

void AHitAndBlow_PC::EnablePause()
{
	Super::EnablePause();

	// PauseModeBindに変更
	RemoveBindAction();
	BindPauseModeAction();

	UE_LOG(LogTemp, Warning, TEXT("IsPause"));
}

void AHitAndBlow_PC::DisablePause()
{
	Super::DisablePause();
	EHitAndBlowState CurState = GetWorld()->GetGameState<AHitAndBlow_GSB>()->GetCurrentState();

	RemoveBindAction();
	if (CurState == EHitAndBlowState::PLAY)
	{
		// PlayModeBindに変更
		BindPlayModeAction();
	}
	else
	{
		BindPauseAction();
	}
	UE_LOG(LogTemp, Warning, TEXT("IsNotPause"));
}

void AHitAndBlow_PC::NoneAction()
{
}


/*
void AHitAndBlow_PC::Setup(TObjectPtr<UInputComponent> MyInputComponent)
{
	Super::Setup(MyInputComponent);

	// Defaultで所持しているInputComponentをEnhancedInputComponentにCast
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(MyInputComponent))
	{
		// 関数とInputActionを紐づける
		EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::OnPause);
		EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::OnDone);
		EnhancedInputComponent->BindAction(InputToCancel, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::OnCancel);
		EnhancedInputComponent->BindAction(InputToSelectX, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::OnSelectX);
		EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::OnSelectY);
	}
}
*/

/*
void AHitAndBlow_PC::OnPause(const FInputActionValue& Value)
{
	if (bIsPressed) { return; }
	bIsPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("OnPause!!"));

	// 現在のStateを取得
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();


	if (AHitAndBlow_GSB::EHitAndBlowState::PLAY == CurState)
	{
		// GameのPause状態を切り替える
		SetPause(true);

		TObjectPtr<AHitAndBlow_HUD> HUD = GetHUD<AHitAndBlow_HUD>();
		// Pauseメニューの表示
		HUD->AddUI(HUD->GetPauseUI());

		MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PAUSE);
	}

	else if (AHitAndBlow_GSB::EHitAndBlowState::PAUSE == CurState)
	{
		// GameのPause状態を切り替える
		SetPause(false);

		TObjectPtr<UPauseMenu_UW> PauseMenuUI = Cast<UPauseMenu_UW>(HUD->GetPauseUI());
		// Pauseメニューの非表示
		PauseMenuUI->OnCancel(this);

		MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PLAY);
	}

	bIsPressed = false;
}

void AHitAndBlow_PC::OnDone(const FInputActionValue& Value)
{
	if (bIsPressed) { return; }

	// 現在のStateを取得
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();

	bIsPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("OnDone!!"));


	if (AHitAndBlow_GSB::EHitAndBlowState::PAUSE == CurState)
	{
		TObjectPtr<AHitAndBlow_HUD> HUD = GetHUD<AHitAndBlow_HUD>();
		TObjectPtr<UPauseMenu_UW> PauseMenuUI = Cast<UPauseMenu_UW>(HUD->GetPauseUI());
		PauseMenuUI->OnButton(this);
	}

	else if (AHitAndBlow_GSB::EHitAndBlowState::PLAY == CurState)
	{
		// TurnMarkにTargetしているなら
		if (Board->GetIsTargetTurnMark())
		{
			// 答え合わせをする
			MyGameState->Answer();

			int CurTurn = MyGameState->GetCurTurn();
			TArray<FVector> LocationList = Board->GetResultPinLocationList(CurTurn);
			MyGameState->SetResultPin(LocationList);

			MyGameState->NextTurn();
			Board->TurnInit(MyGameState->GetCurTurn());
			bIsPressed = false;
			return;
		}
		else
		{
			// PinSpawn
			// 現在のカーソル位置番号を取得
			int ColCursorIndex = Board->GetColCursorIndex();
			int RowCursorIndex = Board->GetRowCursorIndex();

			// 位置番号に対応したLocationを取得
			FVector CurChoisePoint = Board->GetCurrentChoisePinPointByIndex(ColCursorIndex);

			// 位置番号に対応したPinTypeを取得
			EPinType CurSelectPinType = MyGameState->GetSelectPinTypeByIndex(RowCursorIndex);

			// PinをStateで生成し、管理する
			MyGameState->SetCurrentChoisePin(ColCursorIndex, CurSelectPinType, CurChoisePoint);

			UE_LOG(LogTemp, Warning, TEXT("Spawn!!"));
		}

		// 解答可能かチェックする
		if (MyGameState->CheckCanAnswer())
		{
			// 一度TurnMarkCursorを表示する
			Board->CanTargetTurnMark(MyGameState->GetCurTurn());
		}
		else
		{
			// カーソルを1つ進める
			Board->ColCursorIncrement();
		}
	}

	else if (AHitAndBlow_GSB::EHitAndBlowState::RESULT == CurState)
	{

	}

	bIsPressed = false;
}

void AHitAndBlow_PC::OnCancel(const FInputActionValue& Value)
{
	
	if (bIsPressed) { return; }

	// 現在のStateを取得
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();

	bIsPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("OnCancel!!"));

	if (AHitAndBlow_GSB::EHitAndBlowState::PAUSE == CurState)
	{
		TObjectPtr<AHitAndBlow_HUD> HUD = GetHUD<AHitAndBlow_HUD>();
		TObjectPtr<UPauseMenu_UW> PauseMenuUI = Cast<UPauseMenu_UW>(HUD->GetPauseUI());
		PauseMenuUI->OnCancel(this);

		MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PLAY);
	}

	bIsPressed = false;
}

void AHitAndBlow_PC::OnSelectX(const FInputActionValue& Value)
{
	if (bIsPressed) { return; }

	// 現在のStateを取得
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();

	bIsPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("OnSelectX!!"));

	if (AHitAndBlow_GSB::EHitAndBlowState::PLAY == CurState)
	{
		Board->ChangeRowCursorLocation(Value.Get<float>());
	}

	bIsPressed = false;
}

void AHitAndBlow_PC::OnSelectY(const FInputActionValue& Value)
{
	if (bIsPressed) { return; }

	// 現在のStateを取得
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();

	bIsPressed = true;
	UE_LOG(LogTemp, Warning, TEXT("OnSelectY!!"));

	if (AHitAndBlow_GSB::EHitAndBlowState::PAUSE == CurState)
	{
		TObjectPtr<AHitAndBlow_HUD> HUD = GetHUD<AHitAndBlow_HUD>();
		TObjectPtr<UPauseMenu_UW> PauseMenuUI = Cast<UPauseMenu_UW>(HUD->GetPauseUI());
		PauseMenuUI->OnSelect(Value.Get<float>());
	}

	else if (AHitAndBlow_GSB::EHitAndBlowState::PLAY == CurState)
	{
		Board->ChangeColCursorLocation(Value.Get<float>());
	}
	
	else if (AHitAndBlow_GSB::EHitAndBlowState::RESULT == CurState)
	{

	}

	bIsPressed = false;
}
*/

