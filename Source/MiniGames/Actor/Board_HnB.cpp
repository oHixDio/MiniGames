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

	// Root生成
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	// Cursor生成
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

	// Cursorを非表示にする
	SetHiddenCursor(true);

	// カーソルを初期位置に移動させる
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
	// チョイスポイントリセット
	CurrentChoisePoints.Empty();
	// ターンに対応したチョイスポイントに変更
	for (int i = 0; i < ChoisePinPoints.Num() / 8; i++)
	{
		int Index = (CurrentTurn - 1) * (ChoisePinPoints.Num() / 8) + i;
		// 0 * 4 + i = 0,1,2,3
		// 1 * 4 + i = 4,5,6,7
		// 7 * 4 + i = 28,29,30,31
		CurrentChoisePoints.Add(ChoisePinPoints[Index]);
	}

	// Infoリセット
	ChoiseIndex = 0;
	SelectIndex = 0;
	TurnMarkIndex = CurrentTurn - 1;
	bCanSelectTurnMark = false;
	bIsTargetTurnmark = false;

	// カーソルの位置を移動
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

		// 1→2→3→0→1
		++SelectIndex %= (SelectPinPoints.Num());
	}
	else
	{
		// 0→3→2→1→0
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
		// 1→2→3→0→1
		++ChoiseIndex %= (CurrentChoisePoints.Num());
	}
	else
	{
		// 0→3→2→1→0
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

	// 1→2→3→0→1
	++ChoiseIndex %= (CurrentChoisePoints.Num());

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ChoiseIndex]->GetComponentLocation() + CursorLocationOffset
	);
}

void ABoard_HnB::CanTargetTurnMark()
{
	// 現在の選択ポイント配列の最後に、ターンマークポジションも追加する
	CurrentChoisePoints.Add(ResultAreaPoints[TurnMarkIndex]);

	// 追加したPointの場所にカーソルを移動する
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
	// Cursorを非表示にする
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(ResultCursor, true);
	ComponentSetHidden(OkeyText, true);

	if (!bIsHidden)
	{
		if (4 == ChoiseIndex)
		{
			// 縦横Cursorを非表示にして、TurnMarkCursorを表示する
			ComponentSetHidden(ColCursor, true);
			ComponentSetHidden(RowCursor, true);
			ComponentSetHidden(ResultCursor, false);
		}
		else
		{
			// 縦横Cursorを表示して、TurnMarkCursorを非表示にする
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


/******************** オリジナルメソッド ********************/
/*
void ABoard_HnB::Setup()
{
	// フラグを下す
	bCanTargetTurnMark = false;
	IsTargetTurnMark = false;

	// Cursorを非表示にする
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(TurnMarkCursor, true);

	// カーソルを初期位置に移動させる
	ColCursor->SetRelativeLocation(ChoisePinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[0]->GetComponentLocation() + CursorLocationOffset);
	TurnMarkCursor->SetRelativeLocation(TurnMarkPoints[0]->GetComponentLocation() + CursorLocationOffset);
}
*/
/*
void ABoard_HnB::TurnInit(int CurTurn)
{
	// フラグを下す
	bCanTargetTurnMark = false;
	IsTargetTurnMark = false;

	// Cursorを非表示にする
	ComponentSetHidden(ColCursor, true);
	ComponentSetHidden(RowCursor, true);
	ComponentSetHidden(TurnMarkCursor, true);

	// ターンに対応したチョイスポイントに変更
	ChangeCurrentChoisePoints(CurTurn);

	// カーソル番号リセット
	ColCursorIndex = 0;
	RowCursorIndex = 0;

	// カーソルの位置を移動
	ColCursor->SetRelativeLocation(CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset);
	RowCursor->SetRelativeLocation(SelectPinPoints[RowCursorIndex]->GetComponentLocation() + CursorLocationOffset);
	TurnMarkCursor->SetRelativeLocation(TurnMarkPoints[CurTurn - 1]->GetComponentLocation() + CursorLocationOffset);

	// 縦横のカーソル表示
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
		// 1→2→3→0→1
		++ColCursorIndex %= (CurrentChoisePoints.Num());
	}
	else
	{
		// 0→3→2→1→0
		ColCursorIndex--;
		if (ColCursorIndex < 0)
		{
			ColCursorIndex = (CurrentChoisePoints.Num() - 1);
		}
	}
	
	// TurnMarkをTargetしているかチェック
	CheckTargetTurnMark();

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset
	);
	UE_LOG(LogTemp, Warning, TEXT("ColCursorIndex:%d"), ColCursorIndex);
	// 更新したインデックスを返す
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

		// 1→2→3→0→1
		++RowCursorIndex %= (SelectPinPoints.Num());
	}
	else
	{
		// 0→3→2→1→0
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
	// 更新したインデックスを返す
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
		// 縦横Cursorを非表示にして、TurnMarkCursorを表示する
		ComponentSetHidden(ColCursor, true);
		ComponentSetHidden(RowCursor, true);
		ComponentSetHidden(TurnMarkCursor, false);
	}
	else
	{
		// 縦横Cursorを表示して、TurnMarkCursorを非表示にする
		ComponentSetHidden(ColCursor, false);
		ComponentSetHidden(RowCursor, false);
		ComponentSetHidden(TurnMarkCursor, true);
	}
}*/
/*
void ABoard_HnB::CheckTargetTurnMark()
{
	// TurnMarkをTargetできるなら
	if (bCanTargetTurnMark)
	{
		// TurnMarkをターゲットしているかどうか
		if (ColCursorIndex == 4)
		{
			IsTargetTurnMark = true;
		}
		else
		{
			IsTargetTurnMark = false;
		}
		// カーソルの表示切替
		TargetTurnMark(IsTargetTurnMark);
	}
}*/
/*
void ABoard_HnB::ColCursorIncrement()
{
	// 1→2→3→0→1
	++ColCursorIndex %= (CurrentChoisePoints.Num());

	CheckTargetTurnMark();

	// ColCursorLocation Update
	ColCursor->SetRelativeLocation
	(
		CurrentChoisePoints[ColCursorIndex]->GetComponentLocation() + CursorLocationOffset
	);
}*/