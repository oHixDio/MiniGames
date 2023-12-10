// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlow_PC.h"
#include "../GameModeBase/HitAndBlow_GMB.h"
#include "../GameStateBase/HitAndBlow_GSB.h"
#include "../HUD/HitAndBlow_HUD.h"
#include "../Actor/Board_HnB.h"
#include "../UserWidget/PauseMenu_UW.h"
#include <MiniGames/UserWidget/Result_UW.h>
#include "InputAction.h" // �ǉ�
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // �ǉ�
#include "EnhancedInputSubsystems.h" // �ǉ�
#include <Kismet/GameplayStatics.h>

AHitAndBlow_PC::AHitAndBlow_PC()
	:Super()
{
	
}

void AHitAndBlow_PC::BeginPlay()
{
	Super::BeginPlay();

	// InputMappingContext��ݒ�
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
UE_LOG(LogTemp, Warning, TEXT("HitAndBlow_PC"));
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	/*
	Setup(InputComponent);

	// GameStateBase�擾
	MyGameState = GetWorld()->GetGameState<AHitAndBlow_GSB>();

	// Board�擾
	Board = Cast<ABoard_HnB>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard_HnB::StaticClass()));
	
	// kari
	Board->TurnInit(MyGameState->GetCurTurn());

	MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PLAY);
	*/
}

void AHitAndBlow_PC::BindPauseAction()
{
	// Pause�݂̂ł���
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::EnablePause));
	}
}

void AHitAndBlow_PC::BindPauseModeAction()
{
	// Pause��Ԃ̑���
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::DisablePause));

		// PauseMenu�̋@�\���o�C���h
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
	// Result_UW����@�\��I��
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		// PauseMenu�̋@�\���o�C���h
		if (UResult_UW* ResultUI = Cast<UResult_UW>(GetHUD<AHitAndBlow_HUD>()->GetResultUI()))
		{
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, ResultUI, &UResult_UW::OnButton));
			BindingActionList.Add(EnhancedInputComponent->BindAction(InputToSelectY, ETriggerEvent::Triggered, ResultUI, &UResult_UW::OnSelect));
		}
	}
	
}

void AHitAndBlow_PC::BindPlayModeAction()
{
	// Play��Ԃ̑���
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		BindingActionList.Add(EnhancedInputComponent->BindAction(InputToPause, ETriggerEvent::Triggered, this, &AHitAndBlow_PC::EnablePause));

		// Board�̋@�\���o�C���h
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
		// Bind�ς�Action�����O��
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

	// PauseModeBind�ɕύX
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
		// PlayModeBind�ɕύX
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

	// Default�ŏ������Ă���InputComponent��EnhancedInputComponent��Cast
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(MyInputComponent))
	{
		// �֐���InputAction��R�Â���
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

	// ���݂�State���擾
	AHitAndBlow_GSB::EHitAndBlowState CurState = MyGameState->GetCurrentState();


	if (AHitAndBlow_GSB::EHitAndBlowState::PLAY == CurState)
	{
		// Game��Pause��Ԃ�؂�ւ���
		SetPause(true);

		TObjectPtr<AHitAndBlow_HUD> HUD = GetHUD<AHitAndBlow_HUD>();
		// Pause���j���[�̕\��
		HUD->AddUI(HUD->GetPauseUI());

		MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PAUSE);
	}

	else if (AHitAndBlow_GSB::EHitAndBlowState::PAUSE == CurState)
	{
		// Game��Pause��Ԃ�؂�ւ���
		SetPause(false);

		TObjectPtr<UPauseMenu_UW> PauseMenuUI = Cast<UPauseMenu_UW>(HUD->GetPauseUI());
		// Pause���j���[�̔�\��
		PauseMenuUI->OnCancel(this);

		MyGameState->ChangeState(AHitAndBlow_GSB::EHitAndBlowState::PLAY);
	}

	bIsPressed = false;
}

void AHitAndBlow_PC::OnDone(const FInputActionValue& Value)
{
	if (bIsPressed) { return; }

	// ���݂�State���擾
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
		// TurnMark��Target���Ă���Ȃ�
		if (Board->GetIsTargetTurnMark())
		{
			// �������킹������
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
			// ���݂̃J�[�\���ʒu�ԍ����擾
			int ColCursorIndex = Board->GetColCursorIndex();
			int RowCursorIndex = Board->GetRowCursorIndex();

			// �ʒu�ԍ��ɑΉ�����Location���擾
			FVector CurChoisePoint = Board->GetCurrentChoisePinPointByIndex(ColCursorIndex);

			// �ʒu�ԍ��ɑΉ�����PinType���擾
			EPinType CurSelectPinType = MyGameState->GetSelectPinTypeByIndex(RowCursorIndex);

			// Pin��State�Ő������A�Ǘ�����
			MyGameState->SetCurrentChoisePin(ColCursorIndex, CurSelectPinType, CurChoisePoint);

			UE_LOG(LogTemp, Warning, TEXT("Spawn!!"));
		}

		// �𓚉\���`�F�b�N����
		if (MyGameState->CheckCanAnswer())
		{
			// ��xTurnMarkCursor��\������
			Board->CanTargetTurnMark(MyGameState->GetCurTurn());
		}
		else
		{
			// �J�[�\����1�i�߂�
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

	// ���݂�State���擾
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

	// ���݂�State���擾
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

	// ���݂�State���擾
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

