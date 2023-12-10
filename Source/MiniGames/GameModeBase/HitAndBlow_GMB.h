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
	* 1  GameFailed����CorrectPin�̐���								// OK
	* 2  Answer�g���K�[��AOKUI�̕\��									// OK
	* 3  OKUI�̕\���ɔ����ATurnMark�J�[�\����ResultCursor�ɕύX����		// OK
	* 4  Pin�̐������̓J�[�\�����\���A���͂��|�[�Y�݂̂ɂ���			// OK
	* ----- 12/5 Task -----
	* 5  BGM�̒ǉ�
	* 6  SE�̒ǉ�
	* 7  �^�C�g���̒���												// OK
	* ----- 12/6 Task -----
	* 8  �Q�v���C���[�Ή�
	* ----- 12/7 Task -----
	* HitAndBlow��������쐬
	* GitHub�Ƀr���h�f�[�^�ƃ\�[�X�R�[�h�f�[�^�ڂ��� // ���Ԃ����
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
	/// InputAction�Ƃ���Board�̋@�\��o�^���鎞�APlayerController�ɓ`����ׂɍ쐬
	/// </summary>
	const TObjectPtr<class ABoard_HnB> GetBoard() const ;

	const TArray<TObjectPtr<class AHitAndBlow_PC>> GetPlayerList() const { return HitAndBlowPlayerList; }

	// -------------------------------------------------- //
	// --------------- BlueprintCallables --------------- //
	// -------------------------------------------------- //
public:
	/// <summary>
	/// �Q�[���J�n���A��x�����s����Anim
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void StartGameAnimation();

	/// <summary>
	/// �𓚎���Ami,
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void AnswerAnimation(bool bIsCorrect);

	/// <summary>
	/// Result�܂ł�Anim
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void EndGameAnimation();

	/// <summary>
	/// Animation���I�������Ƃ��̃C�x���g�֐�
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void FinishAnimation();

	/// <summary>
	/// 4�́HPin�����������
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void UnknownPinSpawn();

	/// <summary>
	/// 4�̌��ʃs�������������
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void ResultPinSpawn();

	/// <summary>
	/// 4�̐����s�������������
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CorrectPinSpawn();

	// -------------------------------------------------- //
	// ---------------------- Main ---------------------- //
	// -------------------------------------------------- //
public:

	/// <summary>
	/// Init()�̓^�[���J�n���Ɏ��s����邪
	/// Setup()��BeginPlay�Ŏ��s�����
	/// </summary>
	void Setup();

	/// <summary>
	/// GameMode,GameState,Board�������������B
	/// Turn��i�߂鏈���̋L�q�͕ʂł���
	/// </summary>
	void Init();

	/// <summary>
	/// ���݃Z���N�g�J�[�\���őI������Ă���s���𐶐�����
	/// ���݃`���C�X�J�[�\���őI������Ă���ʒu��
	/// </summary>
	void SpawnPin();

	/// <summary>
	/// �����ŗ^�����s���̎�ނƈʒu�Ƀs���𐶐�����
	/// </summary>
	class APin& SpawnPin(EPinType Type, FVector Location) const;

	/// <summary>
	/// �f�X�g���C�̋L�q�͕ʂōs���Ă��邽�߁A�󗓊֐��ł���B
	/// </summary>
	void DestroyPin();

	/// <summary>
	/// �`���C�X�J�[�\���ɂ���čs����A�N�V�������Ⴄ
	/// �`���C�X�J�[�\����ResultArea�ɂ���ꍇ�A�A���T�[
	/// ����ȊO�̓s������
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
