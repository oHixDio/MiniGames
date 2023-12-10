// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "InputActionValue.h" // 追加
#include <MiniGames/Enum/EPinType.h>
#include "Board_HnB.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API ABoard_HnB : public AMyActor
{
	GENERATED_BODY()


protected:
	// -------------------------------------------------- //
	// ------------------- Components ------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> CorrectPinPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> SelectPinPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> ChoisePinPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> ResultPinPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> ResultAreaPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Points")
	TArray<USceneComponent*> CurrentChoisePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Cursor")
	TObjectPtr<class UWidgetComponent> ColCursor{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Cursor")
	TObjectPtr<class UWidgetComponent> RowCursor{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Cursor")
	TObjectPtr<class UWidgetComponent> ResultCursor{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Cursor")
	TObjectPtr<class UWidgetComponent> OkeyText{ nullptr };

	// -------------------------------------------------- //
	// ---------------------- Info ---------------------- //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere, Category = "Info|Index")
	int ChoiseIndex{ 0 };

	UPROPERTY(VisibleAnywhere, Category = "Info|Index")
	int SelectIndex{ 0 };

	UPROPERTY(VisibleAnywhere, Category = "Info|Index")
	int TurnMarkIndex{ 0 };

	/// <summary>
	/// TurnMarkをSelectできるかどうか
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Info|bool")
	bool bCanSelectTurnMark{ false };

	UPROPERTY(VisibleAnywhere, Category = "Info|bool")
	bool bIsTargetTurnmark{ false };


	// -------------------------------------------------- //
	// --------------------- Sounds --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> SelectSE;


	// -------------------------------------------------- //
	// --------------------- Others --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere, Category = "Other")
	FVector CursorLocationOffset{ FVector(0,0,3) };




	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
public:
	ABoard_HnB();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// -------------------------------------------------- //
	// -------------------- Accesser -------------------- //
	// -------------------------------------------------- //
public:
	/// <summary>
	/// ピンのスポーンに必要なインデックス番号を渡す　
	/// </summary>
	const int GetSelectIndex() const { return SelectIndex; }

	const int GetChoiseIndex() const { return ChoiseIndex; }

	const bool GetCanSelectTurnMark() const { return bCanSelectTurnMark; }

	const bool GetIsTagetTurnMark() const { return bIsTargetTurnmark; }

	const TArray<FVector> GetCorrectPinPointList() const;

	const FVector GetCorrectPinPointByIndex(int Index) const;

	const TArray<FVector> GetResultPinPointList(int CurTurn) const;

	const FVector GetResultPinPointByIndex(int CurTurn, int Index) const;

	/// <summary>
	/// ピンのスポーンに必要な位置情報を渡す
	/// </summary>
	const FVector GetChoisePoints() const { return CurrentChoisePoints[ChoiseIndex]->GetComponentLocation(); }

	/*
	const FVector GetCorrectPinPointByIndex(int i) const;

	const TArray<FVector> GetResultPinLocationList(int CurrentTurn) const;

	const FVector GetCurrentChoisePinPointByIndex(int i) const;

	const int GetColCursorIndex() const { return ColCursorIndex; }
	
	const int GetRowCursorIndex() const { return RowCursorIndex; }
	*/

	// -------------------------------------------------- //
	// --------------- BlueprintCallable  --------------- //
	// -------------------------------------------------- //
public:

	UFUNCTION(BlueprintCallable)
	void SetPoints
	(
		TArray<USceneComponent*> NewCorrectPinPoints,
		TArray<USceneComponent*> NewSelectPinPoints,
		TArray<USceneComponent*> NewChoisePinPoints,
		TArray<USceneComponent*> NewResultPinPoints,
		TArray<USceneComponent*> NewResultAreaPoints
	);
	

	// -------------------------------------------------- //
	// --------------------- Others --------------------- //
	// -------------------------------------------------- //
public:

	void BoardInit(int CurrentTurn);

	void TargetSelectPointUpdate(const FInputActionValue& Value);

	void TargetChoisePointUpdate(const FInputActionValue& Value);

	void TargetChoisePointIncrement();

	void CanTargetTurnMark();

	void SetHiddenCursor(bool bIsHidden);

private:
	/// <summary>
	/// ChoiseIndexがTurnMarkを指しているか判定
	/// その状態を表す変数を更新
	/// 指している場合TurnMarkCursorを表示
	/// 指していない場合、通常Cursorを表示
	/// </summary>
	void TargetTurnMark();
	/*
	void Setup();

	void TurnInit(int CurTurn);

	void ChangeCurrentChoisePoints(int CurrentTurn);

	const int ChangeColCursorLocation(float Value);

	const int ChangeRowCursorLocation(float Value);

	void ChangeTurnMarkLocation(int CurrentTurn);

	void CanTargetTurnMark(int CurrentTurn);

	void TargetTurnMark(bool bIsTarget);

	void CheckTargetTurnMark();

	void ColCursorIncrement();
	*/
};
