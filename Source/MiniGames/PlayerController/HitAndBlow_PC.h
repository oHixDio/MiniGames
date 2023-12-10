// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "InputActionValue.h" // 追加
#include "../Enum/EHitAndBlowState.h"
#include "HitAndBlow_PC.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API AHitAndBlow_PC : public AMyPlayerController
{
	GENERATED_BODY()

protected:
	// -------------------------------------------------- //
	// -------------- InputMappingContexts  ------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputMappingContext")
	TObjectPtr<class UInputMappingContext> DefaultIMC{ nullptr };


	// -------------------------------------------------- //
	// ------------------ InputActions  ----------------- //
	// -------------------------------------------------- //
	// InputActionはPlayerContrpllerに配置
	// InputToOOOOOをテンプレとする
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToPause{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToDone{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToCancel{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToSelectX{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToSelectY{ nullptr };


	// UPROPERTYはつけられない
	TArray<FInputBindingHandle> BindingActionList;

	// UPROPERTY(VisibleAnywhere, Category = "EnhancedInput|InputActions")

	// -------------------------------------------------- //
	// --------------------- Others  -------------------- //
	// -------------------------------------------------- //
	UPROPERTY(VisibleAnywhere)
	bool bIsPressed{ false };



	// -------------------------------------------------- //
	// -------------------- Defaults -------------------- //
	// -------------------------------------------------- //
public:
	AHitAndBlow_PC();

	virtual void BeginPlay() override;


	// -------------------------------------------------- //
	// ------------------- BindActions ------------------ //
	// -------------------------------------------------- //
public:

	void BindPauseAction();

	void BindPauseModeAction();

	void BindResultModeAction();
	
	void BindPlayModeAction();

	void RemoveBindAction();

	void AddBindAction(EHitAndBlowState State);
	// -------------------------------------------------- //
	// --------------------- Others  -------------------- //
	// -------------------------------------------------- //
public:

	void SetPlayerEnableState(bool bIsEnable);

	void EnablePause() override;

	void DisablePause() override;

	void NoneAction();


	/*
public:
	void Setup(TObjectPtr<UInputComponent> MyInputComponent) override;
	*/
	/*
	// -------------------------------------------------- //
	// -------------------- Inputter  ------------------- //
	// -------------------------------------------------- //
	// InputActionにBindするメソッド群
	// OnOOOOOをテンプレとする
public:
	void OnPause(const FInputActionValue& Value);

	void OnDone(const FInputActionValue& Value);

	void OnCancel(const FInputActionValue& Value);

	void OnSelectX(const FInputActionValue& Value);

	void OnSelectY(const FInputActionValue& Value);
	*/
};
