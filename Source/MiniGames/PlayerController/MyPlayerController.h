// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../MiniGamesGameModeBase.h"
#include "InputActionValue.h" // 追加
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MINIGAMES_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


	
	/*
	* Engineで提供されているメソッドのoverride群
	*/
public:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void RestartLevel() override;


	/*
	* 頻度が高い処理をまとめたメソッド群
	*/
public:
	virtual void Setup(TObjectPtr<UInputComponent> MyInputComponent);

	virtual void EnablePause();

	virtual void DisablePause();

	

};
