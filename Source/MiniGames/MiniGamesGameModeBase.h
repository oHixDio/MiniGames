// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGamesGameModeBase.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MINIGAMES_API AMiniGamesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	/*
	* Engineで提供されているメソッドのoverride群
	*/
public:
	AMiniGamesGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/*
	* 頻度が高い処理をまとめたメソッド群
	*/
public:
	// InputMappingContectを取り付ける
	void AddInputMap(APlayerController* PlayerController, class UInputMappingContext* InputMap, int32 Priority = 0);

	// InputMappingContectを取り外す
	void RemoveInputMap(APlayerController* PlayerController, class UInputMappingContext* InputMap);

	// ActorをInterpToMoveさせるメソッド
	UFUNCTION(BlueprintCallable)
	void MoveActor(class AMyActor* Actor, FVector MoveOffset, float MoveTime);

	/*
	* 主にMenuやゲーム開始、終了時に呼ばれるメソッド群
	*/
public:
	void OpenLevel(FName LevelName);

	void QuitGame();
	

	// 純粋仮想関数にする方法
	// 引数無し戻り値無しの場合、クラス名::関数名,
	// 戻り値ありの場合下記のような記述をする
	//virtual AActor* FixedCameraSponner() PURE_VIRTUAL(AMiniGamesGameModeBase::FixedCameraSponner, return 0;);
	
	/*
	* Controller InputMappingContextの完成	// OK
	* Controller入力の可能と不可能			// OK
	* Cursorの表示非表示						// OK
	* タイトルの作成							// OK
	* タイトルからインゲームへ					// OK
	* ポーズの作成							// OK
	* インゲームからタイトルへ					// OK
	* リスタートレベル						// OK
	* ゲームリザルトの表示
	* Cursorの移動
	* Turnの変更
	* ピンクラス作成、ピン生成、ピンマテリアル設定、ピンアニメーション
	* ピンが４つ生成されたときの処理
	* 答え合わせフローの作成
	* 正解したときの処理作成
	* 勝ち負けの作成
	* SEの挿入
	* エフェクトの挿入
	* -------------------------------------------------------------------------11月終了
	*
	* プレイヤー人数の変更を可能にする
	* それに伴うHitAndBlowの改良
	* SlidePuzzleのボード作成
	* Cursor作成
	* Cursorを二つのコントローラから動かせるようにする
	* Pieceの作成
	* Pieceの移動システム作成
	* Splineの作成
	* MoveObjの作成
	* MoveObjの移動システム作成
	* 失敗フローの作成
	* Diaの作成
	* Diaの生成
	* Diaのポイント作成
	* --------------------------------------------------------------------------12月終了
	*
	*
	*
	*
	*/


};
