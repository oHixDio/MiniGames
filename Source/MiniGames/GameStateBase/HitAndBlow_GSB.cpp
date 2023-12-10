// Fill out your copyright notice in the Description page of Project Settings.


#include "HitAndBlow_GSB.h"
#include "../GameModeBase/HitAndBlow_GMB.h"
#include "../PlayerController/HitAndBlow_PC.h"
#include "../Actor/Board_HnB.h"
#include "../Actor/Pin.h"
#include <Kismet/GameplayStatics.h>
#include "Components/AudioComponent.h"

	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
AHitAndBlow_GSB::AHitAndBlow_GSB()
	:Super()
{
	// Root����
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	CurrentBGM = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
}

void AHitAndBlow_GSB::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

}

void AHitAndBlow_GSB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// -------------------------------------------------- //
// --------------------- State  --------------------- //
// -------------------------------------------------- //
void AHitAndBlow_GSB::ChangeState(EHitAndBlowState NewState)
{
	ExitState(CurrentState);
	CurrentState = NewState;
	EntryState(CurrentState);
}

void AHitAndBlow_GSB::ExitState(EHitAndBlowState CurState)
{
	// GameMode���擾
	TObjectPtr<AHitAndBlow_GMB> MyGameMode = GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>();

	for (TObjectPtr<AHitAndBlow_PC> Controller : MyGameMode->GetPlayerList())
	{
		Controller->RemoveBindAction();
	}

	MyGameMode->GetBoard()->SetHiddenCursor(true);
}

void AHitAndBlow_GSB::EntryState(EHitAndBlowState CurState)
{
	// GameMode���擾
	TObjectPtr<AHitAndBlow_GMB> MyGameMode = GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>();

	for (TObjectPtr<AHitAndBlow_PC> Controller : MyGameMode->GetPlayerList())
	{
		Controller->AddBindAction(CurState);
	}


	if (EHitAndBlowState::BEFORE_PLAY == CurState)
	{
		// BGM���Z�b�g����
		CurrentBGM->SetSound(StartInBGM);
		// BGM���Đ�����
		CurrentBGM->Play();
		// AnimationStart
		MyGameMode->StartGameAnimation();

	}

	if (EHitAndBlowState::PLAY == CurState)
	{
		if (!CurrentBGM->IsPlaying())
		{
			// BGM���Z�b�g����
			CurrentBGM->SetSound(MainBGM);
			// BGM���Đ�����
			CurrentBGM->Play(SoundPlayedTime);
		}
		MyGameMode->GetBoard()->SetHiddenCursor(false);
	}

	if (EHitAndBlowState::RESULT_IN == CurState)
	{
		CurrentBGM->Stop();

		if (CurrentHitAmount == 4)
		{
			// BGM���Z�b�g����
			CurrentBGM->SetSound(ResultInBGM);
		}
		else
		{
			// BGM���Z�b�g����
			CurrentBGM->SetSound(FailedBGM);
		}

		// BGM���Đ�����
		CurrentBGM->Play();

		FTimerHandle SoundTimerHandle;
		GetWorldTimerManager().SetTimer
		(
			SoundTimerHandle,
			[&]()
			{
				ChangeState(EHitAndBlowState::RESULT);
			},
			2.8f,
			false
		);
	}
	if (EHitAndBlowState::RESULT == CurState)
	{
		// BGM���Z�b�g����
		CurrentBGM->SetSound(ResultBGM);
		// BGM���Đ�����
		CurrentBGM->Play();
	}
}


void AHitAndBlow_GSB::AssignChoisePin(APin& Pin, int i)
{
	switch (i)
	{
	case 0:
		if (ChoisePin_0 != nullptr)
		{
			ChoisePin_0->Destroy();
			ChoisePin_0 = nullptr;
		}
		ChoisePin_0 = &Pin;
		break;
	case 1:
		if (ChoisePin_1 != nullptr)
		{
			ChoisePin_1->Destroy();
			ChoisePin_1 = nullptr;
		}
		ChoisePin_1 = &Pin;
		break;
	case 2:
		if (ChoisePin_2 != nullptr)
		{
			ChoisePin_2->Destroy();
			ChoisePin_2 = nullptr;
		}
		ChoisePin_2 = &Pin;
		break;
	case 3:
		if (ChoisePin_3 != nullptr)
		{
			ChoisePin_3->Destroy();
			ChoisePin_3 = nullptr;
		}
		ChoisePin_3 = &Pin;
		break;
	default:
		break;
	}
}


bool AHitAndBlow_GSB::CheckCanAnswer()
{
	// 4�I�����Ă�Ȃ��
	if (ChoisePin_0 != nullptr &&
		ChoisePin_1 != nullptr &&
		ChoisePin_2 != nullptr &&
		ChoisePin_3 != nullptr
		)
	{
		return true;
	}
	return false;
}

void AHitAndBlow_GSB::SetResultAmount(TArray<EPinType> PinTypeList)
{
	TArray<EPinType> CurrentChoisePinTypeList;
	CurrentChoisePinTypeList.Add(ChoisePin_0->GetType());
	CurrentChoisePinTypeList.Add(ChoisePin_1->GetType());
	CurrentChoisePinTypeList.Add(ChoisePin_2->GetType());
	CurrentChoisePinTypeList.Add(ChoisePin_3->GetType());

	// Hit���𐔂���
	for (int i = 0; i < PinTypeList.Num(); i++)
	{
		if (PinTypeList[i] == CurrentChoisePinTypeList[i])
		{
			CurrentHitAmount++;
		}
	}

	// ��ӂ�List�����
	TSet<EPinType> UniqueTypeList;

	// �I�������s����List�����ӂ̎�ނ����o��
	for (int i = 0; i < CurrentChoisePinTypeList.Num(); i++)
	{
		UniqueTypeList.Add(CurrentChoisePinTypeList[i]);
	}

	// ���List���珇�ԂɎ��o���A�����s�����List�Ɋ܂܂�Ă���Ȃ�Blow
	for (EPinType Type : UniqueTypeList)
	{
		if (PinTypeList.Contains(Type))
		{
			CurrentBlowAmount++;
		}
	}

	CurrentBlowAmount -= CurrentHitAmount;
}

void AHitAndBlow_GSB::Init()
{
	CurrentHitAmount = 0;
	CurrentBlowAmount = 0;
	ChoisePin_0 = nullptr;
	ChoisePin_1 = nullptr;
	ChoisePin_2 = nullptr;
	ChoisePin_3 = nullptr;
}

bool AHitAndBlow_GSB::NextTurn()
{
	if (MAX_TURN != CurTurn)
	{
		CurTurn++;
		return true;
	}
	return false;
}

// -------------------------------------------------- //
// --------------------- Others --------------------- //
// -------------------------------------------------- //


/*
void AHitAndBlow_GSB::Setup()
{
	MyGameMode = GetWorld()->GetAuthGameMode<AHitAndBlow_GMB>();

	// SelectPinType���ݒ肳��Ă��Ȃ��Ȃ�ݒ肷��
	{
		if (SelectPinTypeList.IsEmpty())
		{
			SelectPinTypeList.Add(EPinType::RED);
			SelectPinTypeList.Add(EPinType::GREEN);
			SelectPinTypeList.Add(EPinType::BLUE);
			SelectPinTypeList.Add(EPinType::YELLOW);
			SelectPinTypeList.Add(EPinType::PURPLE);
			SelectPinTypeList.Add(EPinType::BLACK);
		}
	}

	// SelectPin�𐶐�����
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

		for (AActor* Act : Actors)
		{
			if (Cast<APin>(Act))
			{
				SelectPinList.Add(Cast<APin>(Act));
			}
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
}

void AHitAndBlow_GSB::TurnInit()
{
	// �I���s�����ʂ��
	ChoisePins_1 = nullptr;
	ChoisePins_2 = nullptr;
	ChoisePins_3 = nullptr;
	ChoisePins_4 = nullptr;

	// �t���O������
	bCanAnswer = false;

	// �I���s���^�C�v������
	CurrentChoisePinTypeList.Empty();

	// Hit&Blow Amount��������
	CurrentHitAmount = 0;
	CurrentBlowAmount = 0;
}

void AHitAndBlow_GSB::SetUnknownPin(TObjectPtr<class APin> UnknownPin)
{
	UnknownPinList.Add(UnknownPin);
}

void AHitAndBlow_GSB::SetCurrentChoisePin(int i, EPinType Type, FVector Location)
{
	// �璷�����A�z�񂾂Ə�肢�A���S���Y�����v�����Ȃ�
	switch (i)
	{
	case 0:
		if (ChoisePins_1 != nullptr)
		{
			ChoisePins_1 ->Destroy();
		}
		ChoisePins_1 = MyGameMode->SpawnPin(Type, Location);
		break;
	case 1:
		if (ChoisePins_2 != nullptr)
		{
			ChoisePins_2->Destroy();
		}
		ChoisePins_2 = MyGameMode->SpawnPin(Type, Location);
		break;
	case 2:
		if (ChoisePins_3 != nullptr)
		{
			ChoisePins_3->Destroy();
		}
		ChoisePins_3 = MyGameMode->SpawnPin(Type, Location);
		break;
	case 3:
		if (ChoisePins_4 != nullptr)
		{
			ChoisePins_4->Destroy();
		}
		ChoisePins_4 = MyGameMode->SpawnPin(Type, Location);
		break;
	default:
		break;
	}
}

void AHitAndBlow_GSB::SetResultPin(TArray<FVector> LocationList)
{
	int Index = 0;
	for (int i = 0; i < CurrentHitAmount; i++)
	{
		MyGameMode->SpawnPin(EPinType::HIT, LocationList[i]);
		Index++;
	}

	for (int i = 0; i < CurrentBlowAmount; i++)
	{
		MyGameMode->SpawnPin(EPinType::BLOW, LocationList[Index + i]);
	}
}

const bool AHitAndBlow_GSB::CheckCanAnswer()
{
	// 4�I�����Ă�Ȃ��
	if (ChoisePins_1 != nullptr &&
		ChoisePins_2 != nullptr &&
		ChoisePins_3 != nullptr &&
		ChoisePins_4 != nullptr
		)
	{
		// �𓚂ł���悤�ɂ���
		bCanAnswer = true;
	}

	return bCanAnswer;
}

void AHitAndBlow_GSB::NextTurn()
{
	if (MAX_TURN != CurTurn)
	{
		CurTurn++;
	}

	TurnInit();
}

void AHitAndBlow_GSB::Answer()
{
	// �I�������s���̎�ނ�z��ɂ܂Ƃ߂�
	CurrentChoisePinTypeList.Add(ChoisePins_1->GetType());
	CurrentChoisePinTypeList.Add(ChoisePins_2->GetType());
	CurrentChoisePinTypeList.Add(ChoisePins_3->GetType());
	CurrentChoisePinTypeList.Add(ChoisePins_4->GetType());

	// Hit���𐔂���
	for (int i = 0; i < CorrectPinTypeList.Num(); i++)
	{
		if (CorrectPinTypeList[i] == CurrentChoisePinTypeList[i])
		{
			CurrentHitAmount++;
		}
	}

	// Blow���𐔂���

	// ��ӂ�List�����
	TSet<EPinType> UniqueTypeList;

	// �I�������s����List�����ӂ̎�ނ����o��
	for (int i = 0; i < CurrentChoisePinTypeList.Num(); i++)
	{
		UniqueTypeList.Add(CurrentChoisePinTypeList[i]);
	}

	// ���List���珇�ԂɎ��o���A�����s�����List�Ɋ܂܂�Ă���Ȃ�Blow
	for (EPinType Type : UniqueTypeList)
	{
		if (CorrectPinTypeList.Contains(Type))
		{
			CurrentBlowAmount++;
		}
	}

	// BlowAmount����HitAmount������
	CurrentBlowAmount -= CurrentHitAmount;

	UE_LOG(LogTemp, Warning, TEXT("CurrentHitAmount:%d"), CurrentHitAmount);
	UE_LOG(LogTemp, Warning, TEXT("CurrentBlowAmount:%d"), CurrentBlowAmount);
}
*/