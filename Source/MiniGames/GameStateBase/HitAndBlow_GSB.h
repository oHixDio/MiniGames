// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameStateBase.h"
#include "../Enum/EPinType.h"
#include "../Enum/EHitAndBlowState.h"
#include "HitAndBlow_GSB.generated.h"



/**
 * 
 */
UCLASS()
class MINIGAMES_API AHitAndBlow_GSB : public AMyGameStateBase
{
	GENERATED_BODY()


	

protected:
	// -------------------------------------------------- //
	// ------------------ CurrentInfos ------------------ //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere, Category = "CurrentInfos|Turn")
	int MIN_TURN{ 1 };

	UPROPERTY(VisibleAnywhere, Category = "CurrentInfos|Turn")
	int MAX_TURN{ 8 };

	UPROPERTY(VisibleAnywhere, Category = "CurrentInfos|Turn")
	int CurTurn{ MIN_TURN };

	UPROPERTY(VisibleAnywhere, Category = "CurrentInfos|Answer")
	int CurrentHitAmount{ 0 };

	UPROPERTY(VisibleAnywhere, Category = "CurrentInfos|Answer")
	int CurrentBlowAmount{ 0 };


	// -------------------------------------------------- //
	// --------------------- Actors --------------------- //
	// -------------------------------------------------- //
	// Arrayではデストロイ関係で要素順が乱れ、制御が難しいため単体保持する
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class APin> ChoisePin_0{ nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class APin> ChoisePin_1{ nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class APin> ChoisePin_2{ nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actors|Pointer")
	TObjectPtr<class APin> ChoisePin_3{ nullptr };


	// -------------------------------------------------- //
	// --------------------- Sounds --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> MainBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> ResultBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> ResultInBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> StartInBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> FailedBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	class UAudioComponent* CurrentBGM{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	float SoundPlayedTime{ 0 };


	// -------------------------------------------------- //
	// --------------------- Others --------------------- //
	// -------------------------------------------------- //

	EHitAndBlowState CurrentState{ EHitAndBlowState::NONE };



	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
public:

	AHitAndBlow_GSB();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	// -------------------------------------------------- //
	// -------------------- Accessers ------------------- //
	// -------------------------------------------------- //
public:

	const int GetCurTurn() const { return CurTurn; }

	UFUNCTION(BlueprintCallable)
	const int GetHitAmount() const { return CurrentHitAmount; }

	UFUNCTION(BlueprintCallable)
	const int GetBlowAmount() const { return CurrentBlowAmount; }

	const EHitAndBlowState GetCurrentState() const { return CurrentState; }

	/*
	const int GetCurTurn() const { return CurTurn; }

	const EPinType GetSelectPinTypeByIndex(int i) const
	{
		if (i < 0 || i > SelectPinTypeList.Num()) { return EPinType::UNKNOWN; }
		return SelectPinTypeList[i];
	}
	*/
	// -------------------------------------------------- //
	// --------------------- State  --------------------- //
	// -------------------------------------------------- //
public:

	void ChangeState(EHitAndBlowState NewState);

	void ExitState(EHitAndBlowState CurState);

	void EntryState(EHitAndBlowState CurState);

	// -------------------------------------------------- //
	// --------------------- Others --------------------- //
	// -------------------------------------------------- //
public:


	void AssignChoisePin(class APin& Pin, int i);

	bool CheckCanAnswer();

	void SetResultAmount(TArray<EPinType> PinTypeList);

	void Init();

	UFUNCTION(BlueprintCallable)
	bool NextTurn();

	/*
	void Setup();

	void TurnInit();

	void SetUnknownPin(TObjectPtr<class APin> UnknownPin);

	void SetCurrentChoisePin(int i, EPinType Type, FVector Location);

	void SetResultPin(TArray<FVector> LocationList);

	const bool CheckCanAnswer();

	void NextTurn();

	void Answer();
	*/
};
