// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlow_GMB.h"
#include "../PlayerController/HitAndBlow_PC.h"
#include <MiniGames/HUD/HitAndBlow_HUD.h>
#include "../Actor/FixedCamera.h"
#include "../Actor/Board_HnB.h"
#include "../Actor/Pin.h"
#include <MiniGames/GameStateBase/HitAndBlow_GSB.h>
#include "Kismet/GameplayStatics.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "EnhancedInputSubsystems.h" // �ǉ�
#include <MiniGames/UserWidget/Result_UW.h>



// -------------------------------------------------- //
// -------------------- Defaults -------------------- //
// -------------------------------------------------- //

AHitAndBlow_GMB::AHitAndBlow_GMB()
	:Super()
{

}

void AHitAndBlow_GMB::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("HitAndBlow_GMB"));
	Setup();
}

void AHitAndBlow_GMB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//float Rate = GetWorldTimerManager().GetTimerRemaining(AnimationTimerHandle);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Rate);
}

// -------------------------------------------------- //
// -------------------- Accesser -------------------- //
// -------------------------------------------------- //

const TObjectPtr<ABoard_HnB> AHitAndBlow_GMB::GetBoard() const
{
	return Board;
}


// -------------------------------------------------- //
// --------------- BlueprintCallable  --------------- //
// -------------------------------------------------- //
void AHitAndBlow_GMB::FinishAnimation()
{
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();

	if (HnBGameState->GetCurrentState() == EHitAndBlowState::BEFORE_PLAY)
	{
		HnBGameState->ChangeState(EHitAndBlowState::PLAY);
		Init();
	}

	if (HnBGameState->GetCurrentState() == EHitAndBlowState::AFTER_PLAY)
	{
		Result();
	}
}

void AHitAndBlow_GMB::UnknownPinSpawn()
{
	LoopCnt = 0;
	GetWorldTimerManager().SetTimer
	(
		SpawnPinTimerHandle,
		[&]()
		{
			FVector Point;
			Point = Board->GetCorrectPinPointByIndex(LoopCnt) + PinSpawnOffset;
			APin& Pin = SpawnPin(EPinType::UNKNOWN, Point + PinSpawnOffset);
			UnknownPinList.Add(&Pin);
			// loop����������-1���==
			if (LoopCnt == 3)
			{
				GetWorldTimerManager().ClearTimer(SpawnPinTimerHandle);
			}
			LoopCnt++;
		},
		SpawnPinRate,
		true
	);
	
}

void AHitAndBlow_GMB::ResultPinSpawn()
{
	LoopCnt = 0;
	GetWorldTimerManager().SetTimer
	(
		SpawnPinTimerHandle,
		[&]()
		{
			TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();

			// Hit�����񐔂��擾
			int HitAmount = HnBGameState->GetHitAmount();
			// Blow�����񐔂��擾
			int BlowAmount = HnBGameState->GetBlowAmount();

			// Hit����Blow����LoopCnt�ɓ��������Loop���I������
			if (LoopCnt == HitAmount + BlowAmount)
			{
				GetWorldTimerManager().ClearTimer(SpawnPinTimerHandle);
			}
			else
			{
				int CurTurn = HnBGameState->GetCurTurn();
				// Loop�ɑΉ�����Point���擾
				FVector Point = Board->GetResultPinPointByIndex(CurTurn, LoopCnt);
				
				// LoopCnt��HitAmount�����Ȃ�
				if (LoopCnt < HitAmount)
				{
					SpawnPin(EPinType::HIT, Point + PinSpawnOffset);
				}
				else
				{
					SpawnPin(EPinType::BLOW, Point + PinSpawnOffset);
				}
				
				LoopCnt++;
			}
		},
		SpawnPinRate,
		true
	);
}

void AHitAndBlow_GMB::CorrectPinSpawn()
{
	LoopCnt = 0;
	GetWorldTimerManager().SetTimer
	(
		SpawnPinTimerHandle,
		[&]()
		{
			FVector Point;
			Point = Board->GetCorrectPinPointByIndex(LoopCnt) + PinSpawnOffset;

			// UnknownPin���폜
			UnknownPinList[0]->Destroy();
			UnknownPinList.RemoveAt(0);

			// CorrectPin�𐶐�
			SpawnPin(CorrectPinTypeList[LoopCnt], Point + PinSpawnOffset);


			if (LoopCnt == 3)
			{
				GetWorldTimerManager().ClearTimer(SpawnPinTimerHandle);
			}
			LoopCnt++;
		},
		SpawnPinRate,
		true
	);
}

void AHitAndBlow_GMB::Init()
{
	// �{�[�h������������
	Board->BoardInit(GetGameState<AHitAndBlow_GSB>()->GetCurTurn());


	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
	// GameState������������
	HnBGameState->Init();
	
	// TODO: �ʂ̏ꏊ�ōs��
	HnBGameState->ChangeState(EHitAndBlowState::PLAY);


}


// -------------------------------------------------- //
// ---------------------- Main ---------------------- //
// -------------------------------------------------- //

void AHitAndBlow_GMB::Setup()
{
	// Player�����A�擾
	{
		// ����
		// �擾
		TArray<TObjectPtr<AActor>> GetActors;
		UGameplayStatics::GetAllActorsOfClass(this, AHitAndBlow_PC::StaticClass(), GetActors);
		for (TObjectPtr<AActor> act : GetActors)
		{
			if (Cast<AHitAndBlow_PC>(act))
			{
				HitAndBlowPlayerList.Add(Cast<AHitAndBlow_PC>(act));
			}
		}
	}
	// Board�̎擾
	{
		// �擾
		TObjectPtr<AActor> GetActor = UGameplayStatics::GetActorOfClass(this, ABoard_HnB::StaticClass());
		if (GetActor != nullptr)
		{
			Board = Cast<ABoard_HnB>(GetActor);
		}
	}
	// Camera�̎擾
	{
		// �擾
		TObjectPtr<AActor> GetActor = UGameplayStatics::GetActorOfClass(this, AFixedCamera::StaticClass());
		if (GetActor != nullptr)
		{
			FixedCamera = Cast<AFixedCamera>(GetActor);
		}
		FixedCamera->SetActorLocation(-CameraStartOffset + FVector(0,0,700));
	}
	// Player�̏�Ԃ��X�V����
	{
		for (TObjectPtr<AHitAndBlow_PC> Controller : HitAndBlowPlayerList)
		{
			// Player�̎��_���擾����Camera�̎��_�ɂ���
			Controller->SetViewTarget(FixedCamera);

			Controller->SetPlayerEnableState(true);
		}
	}
	// SelectPin�̎擾
	{
		TArray<TObjectPtr<AActor>> GetActors;
		UGameplayStatics::GetAllActorsOfClass(this, APin::StaticClass(), GetActors);
		for (TObjectPtr<AActor> act : GetActors)
		{
			if (Cast<APin>(act))
			{
				SelectPinList.Add(Cast<APin>(act));
			}
		}
	}
	// �Z���N�g�s�����X�g�����������Ă��Ȃ��G���[�̌����Ȃ̂ŁA�`�F�b�N����
	{
		if (SelectPinTypeList.Num() < 1)
		{
			SelectPinTypeList.Empty();
			SelectPinTypeList.Add(EPinType::RED);
			SelectPinTypeList.Add(EPinType::GREEN);
			SelectPinTypeList.Add(EPinType::BLUE);
			SelectPinTypeList.Add(EPinType::YELLOW);
			SelectPinTypeList.Add(EPinType::PURPLE);
			SelectPinTypeList.Add(EPinType::BLACK);
		}
	}

	// CorrectPinType�ݒ�
	{
		// RED����BLACK�܂ł͈̔͂ɍi�邽�߂̒������擾
		int Len = (int)EPinType::COUNT - 1;

		// CorrectPinType��4��ތ��܂�܂�
		while (CorrectPinTypeList.Num() < 4)
		{

			// �ǉ�����s���������_���Ō��߂�
			EPinType Pin = (EPinType)(FMath::RandRange(0, Len));

			// ��肪���������蒼��
			if (CorrectPinTypeList.Contains(Pin)) { continue; }

			// �s����ǉ�����
			CorrectPinTypeList.Emplace(Pin);
		}
	}
	// GameState�ݒ�
	{
		TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
		HnBGameState->ChangeState(EHitAndBlowState::BEFORE_PLAY);
	}


}

void AHitAndBlow_GMB::SpawnPin()
{
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();

	// �J�[�\���������A���͂�x�������邽�߃X�e�[�g��ύX����B
	HnBGameState->ChangeState(EHitAndBlowState::AFTER_PLAY);

	// 1������X�e�[�g��������PLAY�ɖ߂�
	float AnswerAnimationRate = SpawnPinRate;
	GetWorldTimerManager().SetTimer
	(
		AnimationTimerHandle,
		[&]()
		{
			GetGameState<AHitAndBlow_GSB>()->ChangeState(EHitAndBlowState::PLAY);
		},
		AnswerAnimationRate,
		false
	);


	int ChoiseIndex = Board->GetChoiseIndex();
	// Pin�̃^�C�v�ƃX�|�[���ʒu
	// Pin�̃^�C�v�ɑΉ������C���f�b�N�X�ԍ�
	int SelectIndex = Board->GetSelectIndex();
	// �C���f�b�N�X�ԍ��ɑΉ������s���̎��
	EPinType Type = SelectPinTypeList[SelectIndex];
	// �X�|�[���ʒu
	FVector Point = Board->GetChoisePoints() + PinSpawnOffset;

	// �s���̐������s��
	TObjectPtr<APin> Pin = GetWorld()->SpawnActor<APin>(BP_Pin, Point, FRotator(0));
	if (Pin != nullptr)
	{
		// �s���̐�����̏������s��
		Pin->Setup(Type);
		// ���������s����ێ�����
		HnBGameState->AssignChoisePin(*Pin, ChoiseIndex);
	}

	// TurnMark���I���ł����Ԃł͂Ȃ��̂Ȃ�
	if (!Board->GetCanSelectTurnMark())
	{
		// Pin���S��������Ă��邩�`�F�b�N
		if (HnBGameState->CheckCanAnswer())
		{
			// �S��������Ă����ꍇ�ABoard�̏�Ԃ��X�V������
			// �𓚂ł���悤�ɂ���
			Board->CanTargetTurnMark();
		}

		// ���̃|�C���g�Ɉړ����鏈��
		Board->TargetChoisePointIncrement();
	}
}

APin& AHitAndBlow_GMB::SpawnPin(EPinType Type, FVector Location) const
{
	// �s���̐������s��
	TObjectPtr<APin> Pin = GetWorld()->SpawnActor<APin>(BP_Pin, Location, FRotator(0));
	if (Pin != nullptr)
	{
		// �s���̐�����̏������s��
		Pin->Setup(Type);
	}

	return *Pin;
}

void AHitAndBlow_GMB::DestroyPin()
{

}

void AHitAndBlow_GMB::Interact()
{
	if (Board->GetIsTagetTurnMark())
	{
		Answer();
	}
	else
	{
		SpawnPin();
	}
	HitAndBlowPlayerList[0]->ClientPlayForceFeedback(InteractForce);
	UGameplayStatics::SpawnSound2D(GetWorld(), DoneSE, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void AHitAndBlow_GMB::Answer()
{
	UE_LOG(LogTemp, Warning, TEXT("Answer"));
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
	
	HnBGameState->ChangeState(EHitAndBlowState::AFTER_PLAY);

	// Hit��Blow�̐��𐔂���
	HnBGameState->SetResultAmount(CorrectPinTypeList);

	// �������ǂ����m���߂�
	bool bIsCorrect = HnBGameState->GetHitAmount() == 4;


	AnswerAnimation(bIsCorrect);
}

void AHitAndBlow_GMB::Result()
{
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
	// �������ǂ����m���߂�
	bool bIsCorrect = HnBGameState->GetHitAmount() == 4;

	// ����
	if (bIsCorrect)
	{
		GetGameState<AHitAndBlow_GSB>()->ChangeState(EHitAndBlowState::RESULT_IN);
		// Clear
		ShowResultUI(true);
	}
	// �s����
	else
	{
		// ���̃^�[���ɐi�߂�
		if (bool bCanNextTurn = HnBGameState->NextTurn())
		{
			Init();
			HnBGameState->ChangeState(EHitAndBlowState::PLAY);
		}
		// ���̃^�[���ɐi�߂��Ȃ�����
		else
		{
			CorrectPinSpawn();

			float AnswerAnimationRate = SpawnPinRate * 4 + 2;
			GetWorldTimerManager().SetTimer
			(
				AnimationTimerHandle,
				[&]()
				{
					GetGameState<AHitAndBlow_GSB>()->ChangeState(EHitAndBlowState::RESULT_IN);
					// Failed
					ShowResultUI(false);
				},
				AnswerAnimationRate,
				false
			);
			
		}
	}
	
}

void AHitAndBlow_GMB::ShowResultUI(bool bIsClear)
{
	TObjectPtr<AHitAndBlow_HUD> HUD = HitAndBlowPlayerList[0]->GetHUD<AHitAndBlow_HUD>();
	TObjectPtr<UResult_UW> ResultUI = Cast<UResult_UW>(HUD->GetResultUI());
	// Result���j���[�̕\��
	HUD->AddUI(ResultUI);
	ResultUI->SetResultText(bIsClear);
}


void AHitAndBlow_GMB::ClearMyTimer()
{
	GetWorldTimerManager().ClearTimer(SpawnPinTimerHandle);
	GetWorldTimerManager().ClearTimer(AnimationTimerHandle);
}


// -------------------------------------------------- //
// -------------------- Checker  -------------------- //
// -------------------------------------------------- //


