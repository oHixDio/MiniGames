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
#include "EnhancedInputSubsystems.h" // 追加
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
			// loopさせたい回数-1回で==
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

			// Hitした回数を取得
			int HitAmount = HnBGameState->GetHitAmount();
			// Blowした回数を取得
			int BlowAmount = HnBGameState->GetBlowAmount();

			// Hit数とBlow数がLoopCntに等しければLoopを終了する
			if (LoopCnt == HitAmount + BlowAmount)
			{
				GetWorldTimerManager().ClearTimer(SpawnPinTimerHandle);
			}
			else
			{
				int CurTurn = HnBGameState->GetCurTurn();
				// Loopに対応したPointを取得
				FVector Point = Board->GetResultPinPointByIndex(CurTurn, LoopCnt);
				
				// LoopCntがHitAmount未満なら
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

			// UnknownPinを削除
			UnknownPinList[0]->Destroy();
			UnknownPinList.RemoveAt(0);

			// CorrectPinを生成
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
	// ボードを初期化する
	Board->BoardInit(GetGameState<AHitAndBlow_GSB>()->GetCurTurn());


	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
	// GameStateを初期化する
	HnBGameState->Init();
	
	// TODO: 別の場所で行う
	HnBGameState->ChangeState(EHitAndBlowState::PLAY);


}


// -------------------------------------------------- //
// ---------------------- Main ---------------------- //
// -------------------------------------------------- //

void AHitAndBlow_GMB::Setup()
{
	// Player生成、取得
	{
		// 生成
		// 取得
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
	// Boardの取得
	{
		// 取得
		TObjectPtr<AActor> GetActor = UGameplayStatics::GetActorOfClass(this, ABoard_HnB::StaticClass());
		if (GetActor != nullptr)
		{
			Board = Cast<ABoard_HnB>(GetActor);
		}
	}
	// Cameraの取得
	{
		// 取得
		TObjectPtr<AActor> GetActor = UGameplayStatics::GetActorOfClass(this, AFixedCamera::StaticClass());
		if (GetActor != nullptr)
		{
			FixedCamera = Cast<AFixedCamera>(GetActor);
		}
		FixedCamera->SetActorLocation(-CameraStartOffset + FVector(0,0,700));
	}
	// Playerの状態を更新する
	{
		for (TObjectPtr<AHitAndBlow_PC> Controller : HitAndBlowPlayerList)
		{
			// Playerの視点を取得したCameraの視点にする
			Controller->SetViewTarget(FixedCamera);

			Controller->SetPlayerEnableState(true);
		}
	}
	// SelectPinの取得
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
	// セレクトピンリストが何も入っていないエラーの原因なので、チェックする
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

	// CorrectPinType設定
	{
		// REDからBLACKまでの範囲に絞るための長さを取得
		int Len = (int)EPinType::COUNT - 1;

		// CorrectPinTypeが4種類決まるまで
		while (CorrectPinTypeList.Num() < 4)
		{

			// 追加するピンをランダムで決める
			EPinType Pin = (EPinType)(FMath::RandRange(0, Len));

			// 被りがあったらやり直し
			if (CorrectPinTypeList.Contains(Pin)) { continue; }

			// ピンを追加する
			CorrectPinTypeList.Emplace(Pin);
		}
	}
	// GameState設定
	{
		TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
		HnBGameState->ChangeState(EHitAndBlowState::BEFORE_PLAY);
	}


}

void AHitAndBlow_GMB::SpawnPin()
{
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();

	// カーソルを消し、入力を遅延させるためステートを変更する。
	HnBGameState->ChangeState(EHitAndBlowState::AFTER_PLAY);

	// 1つ生成後ステートをすぐにPLAYに戻す
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
	// Pinのタイプとスポーン位置
	// Pinのタイプに対応したインデックス番号
	int SelectIndex = Board->GetSelectIndex();
	// インデックス番号に対応したピンの種類
	EPinType Type = SelectPinTypeList[SelectIndex];
	// スポーン位置
	FVector Point = Board->GetChoisePoints() + PinSpawnOffset;

	// ピンの生成を行う
	TObjectPtr<APin> Pin = GetWorld()->SpawnActor<APin>(BP_Pin, Point, FRotator(0));
	if (Pin != nullptr)
	{
		// ピンの生成後の処理を行う
		Pin->Setup(Type);
		// 生成したピンを保持する
		HnBGameState->AssignChoisePin(*Pin, ChoiseIndex);
	}

	// TurnMarkが選択できる状態ではないのなら
	if (!Board->GetCanSelectTurnMark())
	{
		// Pinが４つ生成されているかチェック
		if (HnBGameState->CheckCanAnswer())
		{
			// ４つ生成されていた場合、Boardの状態を更新させる
			// 解答できるようにする
			Board->CanTargetTurnMark();
		}

		// 次のポイントに移動する処理
		Board->TargetChoisePointIncrement();
	}
}

APin& AHitAndBlow_GMB::SpawnPin(EPinType Type, FVector Location) const
{
	// ピンの生成を行う
	TObjectPtr<APin> Pin = GetWorld()->SpawnActor<APin>(BP_Pin, Location, FRotator(0));
	if (Pin != nullptr)
	{
		// ピンの生成後の処理を行う
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

	// HitとBlowの数を数える
	HnBGameState->SetResultAmount(CorrectPinTypeList);

	// 正解かどうか確かめる
	bool bIsCorrect = HnBGameState->GetHitAmount() == 4;


	AnswerAnimation(bIsCorrect);
}

void AHitAndBlow_GMB::Result()
{
	TObjectPtr<AHitAndBlow_GSB> HnBGameState = GetGameState<AHitAndBlow_GSB>();
	// 正解かどうか確かめる
	bool bIsCorrect = HnBGameState->GetHitAmount() == 4;

	// 正解
	if (bIsCorrect)
	{
		GetGameState<AHitAndBlow_GSB>()->ChangeState(EHitAndBlowState::RESULT_IN);
		// Clear
		ShowResultUI(true);
	}
	// 不正解
	else
	{
		// 次のターンに進める
		if (bool bCanNextTurn = HnBGameState->NextTurn())
		{
			Init();
			HnBGameState->ChangeState(EHitAndBlowState::PLAY);
		}
		// 次のターンに進められなかった
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
	// Resultメニューの表示
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


