// Fill out your copyright notice in the Description page of Project Settings.


#include "Board_HnB.h"
#include "Components/WidgetComponent.h"
#include "../Actor/Pin.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"


	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
ABoard_HnB::ABoard_HnB()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root����
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	// Cursor����
	ColCursor = CreateDefaultSubobject<UWidgetComponent>(TEXT("ColCursor"));
	ColCursor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	RowCursor = CreateDefaultSubobject<UWidgetComponent>(TEXT("RowCursor"));
	RowCursor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ResultCursor = CreateDefaultSubobject<UWidgetComponent>(TEXT("SubCursor"));
	ResultCursor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	OkeyText = CreateDefaultSubobject<UWidgetComponent>(TEXT("OkeyText"));
	OkeyText->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABoard_HnB::BeginPlay()
{
	Super::BeginPlay();

	// Cursor���\���ɂ���
	SetHiddenCursor(true);

	// �J�[�\���������ʒu�Ɉړ�������
	ColCursor->SetRelativeLocation(ChoisePinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	ResultCursor->SetRelativeLocation(ResultAreaPoints[0]->GetComponentLocation() + CursorLocationOffset);
	OkeyText->SetRelativeLocation(ResultAreaPoints[0]->GetComponentLocation() + CursorLocationOffset);
}
void ABoard_HnB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const TArray<FVector> ABoard_HnB::GetCorrectPinPointList() const
{
	TArray<FVector> RetLocationList;
	for (USceneComponent* Point : CorrectPinPoints)
	{
		RetLocationList.Add(Point->GetComponentLocation());
	}
	return RetLocationList;
}

const FVector ABoard_HnB::GetCorrectPinPointByIndex(int Index) const
{
	if (Index > CorrectPinPoints.Num()) { return FVector(0); }
	return CorrectPinPoints[Index]->GetComponentLocation();
}

const TArray<FVector> ABoard_HnB::GetResultPinPointList(int CurTurn) const
{
	TArray<FVector> RetLocationList;
	for (int i = 0; i < ResultPinPoints.Num() / 8; i++)
	{
		int Index = (CurTurn - 1) * (ResultPinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		RetLocationList.Add(ResultPinPoints[Index]->GetComponentLocation());
	}
	return RetLocationList;
}

const FVector ABoard_HnB::GetResultPinPointByIndex(int CurTurn, int Index) const
{
	TArray<FVector> PointList;
	for (int i = 0; i < ResultPinPoints.Num() / 8; i++)
	{
		int Index = (CurTurn - 1) * (ResultPinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		PointList.Add(ResultPinPoints[Index]->GetComponentLocation());
	}

	if (Index > PointList.Num()) { return FVector(0); }

	return PointList[Index];
}


// -------------------------------------------------- //
// -------------------- Accesser -------------------- //
// -------------------------------------------------- //
/*
const FVector ABoard_HnB::GetCorrectPinPointByIndex(int i) const
{
	if (i > CorrectPinPoints.Num()) { return FVector(0); }
	return CorrectPinPoints[i]->GetComponentLocation();
}

const TArray<FVector> ABoard_HnB::GetResultPinLocationList(int CurrentTurn) const
{
	TArray<FVector> RetLocationList;
	for (int i = 0; i < ResultPinPoints.Num() / 8; i++)
	{
		int Index = (CurrentTurn - 1) * (ResultPinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		RetLocationList.Add(ResultPinPoints[Index]->GetComponentLocation());
	}
	return RetLocationList;
}

const FVector ABoard_HnB::GetCurrentChoisePinPointByIndex(int i) const
{
	if (i > CurrentChoisePoints.Num()) { return FVector(0); }
	return CurrentChoisePoints[i]->GetComponentLocation();
}
*/


// -------------------------------------------------- //
// --------------- BlueprintCallable  --------------- //
// -------------------------------------------------- //
void ABoard_HnB::SetPoints
(
	TArray<USceneComponent*> NewCorrectPinPoints,
	TArray<USceneComponent*> NewSelectPinPoints,
	TArray<USceneComponent*> NewChoisePinPoints,
	TArray<USceneComponent*> NewResultPinPoints,
	TArray<USceneComponent*> NewResultAreaPoints
)
{
	CorrectPinPoints.Empty();
	SelectPinPoints.Empty();
	ChoisePinPoints.Empty();
	ResultPinPoints.Empty();
	ResultAreaPoints.Empty();

	CorrectPinPoints = NewCorrectPinPoints;
	SelectPinPoints = NewSelectPinPoints;
	ChoisePinPoints = NewChoisePinPoints;
	ResultPinPoints = NewResultPinPoints;
	ResultAreaPoints = NewResultAreaPoints;
}


// -------------------------------------------------- //
// --------------------- Others --------------------- //
// -------------------------------------------------- //
void ABoard_HnB::BoardInit(int CurrentTurn)
{
	// �`���C�X�|�C���g���Z�b�g
	CurrentChoisePoints.Empty();
	// �^�[���ɑΉ������`���C�X�|�C���g�ɕύX
	for (int i = 0; i < ChoisePinPoints.Num() / 8; i++)
	{
		int Index = (CurrentTurn - 1) * (ChoisePinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		CurrentChoisePoints.Add(ChoisePinPoints[Index]);
	}

	// Info���Z�b�g
	ChoiseIndex = 0;
	SelectIndex = 0;
	TurnMarkIndex = CurrentTurn - 1;
	bCanSelectTurnMark = false;
	bIsTargetTurnmark = false;

	// �J�[�\���̈ʒu���ړ�
	ColCursor->SetRelativeLocation(CurrentChoisePoints[ChoiseIndex]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[SelectIndex]->GetComponentLocation() + CursorLocationOffset);
	ResultCursor->SetRelativeLocation(ResultAreaPoints[TurnMarkIndex]->GetComponentLocation() + CursorLocationOffset);
	OkeyText->SetRelativeLocation(ResultAreaPoints[TurnMarkIndex]->GetComponentLocation() + CursorLocationOffset);

	SetHiddenCursor(false);
}

void ABoard_HnB::TargetSelectPointUpdate(const FInputActionValue& Value)
{
	if (SelectPinPoints.Num() < 0) { return; }

	if (bIsTargetTurnmark) { return; }

	float Num = Value.Get<float>();

	// RowCurosorIndex Update
	if (Num > 0)
	{

		// 1��2��3��0��1
		++SelectIndex %= (SelectPinPoints.Num());
	}
	else
	{
		// 0��3��2��1��0
		SelectIndex--;
		if (SelectIndex < 0)
		{
			SelectIndex = (SelectPinPoints.Num() - 1);
		}
	}

	// RowCursorLocation Update
	RowCursor->SetRelativeLocation
	(
		SelectPinPoints[SelectIndex]->GetComponentLocation() + CursorLocationOffset
	);

	// SE Play
	UGameplayStatics::SpawnSound2D(GetWorld(), SelectSE, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void ABoard_HnB::TargetChoisePointUpdate(const FInputActionValue& Value)
{
	if (CurrentChoisePoints.Num() < 0) { return; }

	float Num = Value.Get<float>();
	// ColCursorIndex Update
	if (Num > 0)
	{
		// 1��2��3��0��1
		++ChoiseIndex %= (CurrentChoisePoints.Num());
	}
	else
	{
		// 0��3��2��1��0
		ChoiseIndex--;
		if (ChoiseIndex < 0)
		{
			ChoiseIndex = (CurrentChoisePoints.Num() - 1);
		}
	}

	TargetTurnMark();
	
	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ChoiseIndex]->GetComponentLocation() + CursorLocationOffset
	);

	// SE Play
	UGameplayStatics::SpawnSound2D(GetWorld(), SelectSE, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void ABoard_HnB::TargetChoisePointIncrement()
{
	if (bCanSelectTurnMark) { return; }

	// 1��2��3��0��1
	++ChoiseIndex %= (CurrentChoisePoints.Num());

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ChoiseIndex]->GetComponentLocation() + CursorLocationOffset
	);
}

void ABoard_HnB::CanTargetTurnMark()
{
	// ���݂̑I���|�C���g�z��̍Ō�ɁA�^�[���}�[�N�|�W�V�������ǉ�����
	CurrentChoisePoints.Add(ResultAreaPoints[TurnMarkIndex]);

	// �ǉ�����Point�̏ꏊ�ɃJ�[�\�����ړ�����
	ChoiseIndex = CurrentChoisePoints.Num() - 1;

	bCanSelectTurnMark = true;

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ChoiseIndex]->GetComponentLocation() + CursorLocationOffset
	);

	TargetTurnMark();
}

void ABoard_HnB::SetHiddenCursor(bool bIsHidden)
{
	// Cursor���\���ɂ���
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(ResultCursor, true);
	ComponentSetHidden(OkeyText, true);

	if (!bIsHidden)
	{
		if (4 == ChoiseIndex)
		{
			// �c��Cursor���\���ɂ��āATurnMarkCursor��\������
			ComponentSetHidden(ColCursor, true);
			ComponentSetHidden(RowCursor, true);
			ComponentSetHidden(ResultCursor, false);
		}
		else
		{
			// �c��Cursor��\�����āATurnMarkCursor���\���ɂ���
			ComponentSetHidden(ColCursor, false);
			ComponentSetHidden(RowCursor, false);
			ComponentSetHidden(ResultCursor, true);
		}

		if (bCanSelectTurnMark)
		{
			ComponentSetHidden(OkeyText, false);
		}
	}
	
}

void ABoard_HnB::TargetTurnMark()
{
	if (!bCanSelectTurnMark) { return; }

	if (4 == ChoiseIndex)
	{
		bIsTargetTurnmark = true;
	}
	else
	{
		bIsTargetTurnmark = false;
	}

	SetHiddenCursor(false);
}


/******************** �I���W�i�����\�b�h ********************/
/*
void ABoard_HnB::Setup()
{
	// �t���O������
	bCanTargetTurnMark = false;
	IsTargetTurnMark = false;

	// Cursor���\���ɂ���
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(TurnMarkCursor, true);

	// �J�[�\���������ʒu�Ɉړ�������
	ColCursor->SetRelativeLocation(ChoisePinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	TurnMarkCursor->SetRelativeLocation(TurnMarkPoints[0]->GetComponentLocation() + CursorLocationOffset);
}
*/
/*
void ABoard_HnB::TurnInit(int CurTurn)
{
	// �t���O������
	bCanTargetTurnMark = false;
	IsTargetTurnMark = false;

	// Cursor���\���ɂ���
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(TurnMarkCursor, true);

	// �^�[���ɑΉ������`���C�X�|�C���g�ɕύX
	ChangeCurrentChoisePoints(CurTurn);

	// �J�[�\���ԍ����Z�b�g
	ColCursorIndex = 0;
	RowCursorIndex = 0;

	// �J�[�\���̈ʒu���ړ�
	ColCursor->SetRelativeLocation(CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[RowCursorIndex]->GetComponentLocation() + CursorLocationOffset);
	TurnMarkCursor->SetRelativeLocation(TurnMarkPoints[CurTurn - 1]->GetComponentLocation() + CursorLocationOffset);

	// �c���̃J�[�\���\��
	ComponentSetHidden(ColCursor, false);
	ComponentSetHidden(RowCursor, false);
}
*/
/*
void ABoard_HnB::ChangeCurrentChoisePoints(int CurrentTurn)
{
	CurrentChoisePoints.Empty();

	for (int i = 0; i < ChoisePinPoints.Num() / 8; i++)
	{
		int Index = (CurrentTurn - 1) * (ChoisePinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		CurrentChoisePoints.Add(ChoisePinPoints[Index]);
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentChoisePinPoints:%d"), CurrentChoisePoints.Num());
}
*/
/*
const int ABoard_HnB::ChangeColCursorLocation(float Value)
{
	if (CurrentChoisePoints.Num() < 0) { return 0; }

	// ColCursorIndex Update
	if (Value > 0)
	{
		// 1��2��3��0��1
		++ColCursorIndex %= (CurrentChoisePoints.Num());
	}
	else
	{
		// 0��3��2��1��0
		ColCursorIndex--;
		if (ColCursorIndex < 0)
		{
			ColCursorIndex = (CurrentChoisePoints.Num() - 1);
		}
	}
	
	// TurnMark��Target���Ă��邩�`�F�b�N
	CheckTargetTurnMark();

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset
	);
	UE_LOG(LogTemp, Warning, TEXT("ColCursorIndex:%d"), ColCursorIndex);
	// �X�V�����C���f�b�N�X��Ԃ�
	return ColCursorIndex;
}
*/
/*
const int ABoard_HnB::ChangeRowCursorLocation(float Value)
{
	if (SelectPinPoints.Num() < 0) { return 0; }

	if (IsTargetTurnMark) { return 0; }

	// RowCurosorIndex Update
	if (Value > 0)
	{

		// 1��2��3��0��1
		++RowCursorIndex %= (SelectPinPoints.Num());
	}
	else
	{
		// 0��3��2��1��0
		RowCursorIndex--;
		if (RowCursorIndex < 0)
		{
			RowCursorIndex = (SelectPinPoints.Num() - 1);
		}
	}
	
	// RowCursorLocation Update
	RowCursor->SetRelativeLocation
	(
		SelectPinPoints[RowCursorIndex]->GetComponentLocation() + CursorLocationOffset
	);
	UE_LOG(LogTemp, Warning, TEXT("RowCursorIndex:%d"), RowCursorIndex);
	// �X�V�����C���f�b�N�X��Ԃ�
	return RowCursorIndex;
}
*/
/*
void ABoard_HnB::ChangeTurnMarkLocation(int CurrentTurn)
{
	if (TurnMarkPoints.Num() < 0) { return; }

	// TargetCursorLocation Update
	TurnMarkCursor->SetRelativeLocation
	(
		TurnMarkPoints[CurrentTurn - 1]->GetComponentLocation() + CursorLocationOffset
	);
}
*/


/*
void ABoard_HnB::TargetTurnMark(bool bIsTarget)
{
	if (bIsTarget)
	{
		// �c��Cursor���\���ɂ��āATurnMarkCursor��\������
		ComponentSetHidden(ColCursor, true);
		ComponentSetHidden(RowCursor, true);
		ComponentSetHidden(TurnMarkCursor, false);
	}
	else
	{
		// �c��Cursor��\�����āATurnMarkCursor���\���ɂ���
		ComponentSetHidden(ColCursor, false);
		ComponentSetHidden(RowCursor, false);
		ComponentSetHidden(TurnMarkCursor, true);
	}
}*/
/*
void ABoard_HnB::CheckTargetTurnMark()
{
	// TurnMark��Target�ł���Ȃ�
	if (bCanTargetTurnMark)
	{
		// TurnMark���^�[�Q�b�g���Ă��邩�ǂ���
		if (ColCursorIndex == 4)
		{
			IsTargetTurnMark = true;
		}
		else
		{
			IsTargetTurnMark = false;
		}
		// �J�[�\���̕\���ؑ�
		TargetTurnMark(IsTargetTurnMark);
	}
}*/
/*
void ABoard_HnB::ColCursorIncrement()
{
	// 1��2��3��0��1
	++ColCursorIndex %= (CurrentChoisePoints.Num());

	CheckTargetTurnMark();

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset
	);
}*/