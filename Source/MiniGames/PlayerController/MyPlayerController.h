// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../MiniGamesGameModeBase.h"
#include "InputActionValue.h" // �ǉ�
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MINIGAMES_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


	
	/*
	* Engine�Œ񋟂���Ă��郁�\�b�h��override�Q
	*/
public:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void RestartLevel() override;


	/*
	* �p�x�������������܂Ƃ߂����\�b�h�Q
	*/
public:
	virtual void Setup(TObjectPtr<UInputComponent> MyInputComponent);

	virtual void EnablePause();

	virtual void DisablePause();

	

};
