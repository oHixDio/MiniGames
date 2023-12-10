// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGames/MiniGamesGameModeBase.h"
#include "../Enum/EPinType.h"
#include "../Enum/EHitAndBlowState.h"
#include "HitAndBlow_GMB.generated.h"


/**
 *
 */
UCLASS()
class MINIGAMES_API AHitAndBlow_GMB : public AMiniGamesGameModeBase
{
	GENERATED_BODY()
		
	/*
	* ----- 12/4 Task -----
	* 1  GameFailed時にCorrectPinの生成								// OK
	* 2  Answerトリガー後、OKUIの表示									// OK
	* 3  OKUIの表示に伴い、TurnMarkカーソルをResultCursorに変更する		// OK
	* 4  Pinの生成中はカーソルを非表示、入力をポーズのみにする			// OK
	* ----- 12/5 Task -----
	* 5  BGMの追加
	* 6  SEの追加
	* 7  タイトルの調整												// OK
	* ----- 12/6 Task -----
	* 8  ２プレイヤー対応
	* ----- 12/7 Task -----
	* HitAndBlow制作日誌作成
	* GitHubにビルドデータとソースコードデータ載せる // 時間あれば
	* ----- 12/8 Task -----
	* NextGameDevelopment
	*/
	

protected:
	// -------------------------------------------------- //
	// --------------------- Actors --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TArray<TObjectPtr<class AHitAndBlow_PC>> HitAndBlowPlayerList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TArray<TObjectPtr<class APin>> SelectPinList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TArray<TObjectPtr<class APin>> UnknownPinList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class AFixedCamera> FixedCamera{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class ABoard_HnB> Board{ nullptr };

	UPROPERTY(EditAnyWhere, Category = "Actors|Class")
	TSubclassOf<class APin> BP_Pin;


	// -------------------------------------------------- //
	// -------------------- EPinType -------------------- //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere, Category = "EPinType")
	TArray<EPinType> CorrectPinTypeList;

	UPROPERTY(EditAnywhere, Category = "EPinType")
	TArray<EPinType> SelectPinTypeList;


	// -------------------------------------------------- //
	// --------------------- Timers --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float CameraMovementRate{ 5 };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float CutInUIDisplayRate{ 4 };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float AnimationDelay{ 1 };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float SpawnPinRate{ 0.2f };

	UPROPERTY(EditAnyWhere, Category = "Timers|float")
	float SpawnPinTimer{ 0.2f };


	UPROPERTY(EditAnyWhere, Category = "Timers|Handle")
	FTimerHandle SpawnPinTimerHandle;
	UPROPERTY(EditAnyWhere, Category = "Timers|Handle")
	FTimerHandle AnimationTimerHandle;


	// -------------------------------------------------- //
	// --------------------- Sounds --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> DoneSE;


	// -------------------------------------------------- //
	// --------------------- Others --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnyWhere, Category = "Other")
	FVector PinSpawnOffset{ FVector(0, 0, 7) };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Other")
	FVector CameraStartOffset{ FVector(200, 0, 0) };

	UPROPERTY(VisibleAnywhere, Category = "Other")
	int LoopCnt{ 0 };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Other")
	TObjectPtr<UForceFeedbackEffect> InteractForce;



	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
public:

	AHitAndBlow_GMB();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	// -------------------------------------------------- //
	// -------------------- Accesser -------------------- //
	// -------------------------------------------------- //
public:

	/// <summary>
	/// InputActionとしてBoardの機能を登録する時、PlayerControllerに伝える為に作成
	/// </summary>
	const TObjectPtr<class ABoard_HnB> GetBoard() const ;

	const TArray<TObjectPtr<class AHitAndBlow_PC>> GetPlayerList() const { return HitAndBlowPlayerList; }

	// -------------------------------------------------- //
	// --------------- BlueprintCallables --------------- //
	// -------------------------------------------------- //
public:
	/// <summary>
	/// ゲーム開始時、一度だけ行われるAnim
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void StartGameAnimation();

	/// <summary>
	/// 解答時のAmi,
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void AnswerAnimation(bool bIsCorrect);

	/// <summary>
	/// ResultまでのAnim
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void EndGameAnimation();

	/// <summary>
	/// Animationが終了したときのイベント関数
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void FinishAnimation();

	/// <summary>
	/// 4つの？Pinが生成される
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void UnknownPinSpawn();

	/// <summary>
	/// 4つの結果ピンが生成される
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void ResultPinSpawn();

	/// <summary>
	/// 4つの正解ピンが生成される
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CorrectPinSpawn();

	// -------------------------------------------------- //
	// ---------------------- Main ---------------------- //
	// -------------------------------------------------- //
public:

	/// <summary>
	/// Init()はターン開始時に実行されるが
	/// Setup()はBeginPlayで実行される
	/// </summary>
	void Setup();

	/// <summary>
	/// GameMode,GameState,Boardが初期化される。
	/// Turnを進める処理の記述は別である
	/// </summary>
	void Init();

	/// <summary>
	/// 現在セレクトカーソルで選択されているピンを生成する
	/// 現在チョイスカーソルで選択されている位置に
	/// </summary>
	void SpawnPin();

	/// <summary>
	/// 引数で与えたピンの種類と位置にピンを生成する
	/// </summary>
	class APin& SpawnPin(EPinType Type, FVector Location) const;

	/// <summary>
	/// デストロイの記述は別で行っているため、空欄関数である。
	/// </summary>
	void DestroyPin();

	/// <summary>
	/// チョイスカーソルによって行われるアクションが違う
	/// チョイスカーソルがResultAreaにある場合、アンサー
	/// それ以外はピン生成
	/// </summary>
	void Interact();

	void Answer();

	void Result();

	void ShowResultUI(bool bIsClear);

	void ClearMyTimer();
	

	// -------------------------------------------------- //
	// -------------------- Checker  -------------------- //
	// -------------------------------------------------- //
private:
	
};
