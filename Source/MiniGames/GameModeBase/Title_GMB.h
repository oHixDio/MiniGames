// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MiniGamesGameModeBase.h"
#include "Title_GMB.generated.h"


/**
 * 
 */
UCLASS()
class MINIGAMES_API ATitle_GMB : public AMiniGamesGameModeBase
{
	GENERATED_BODY()


protected:


public:

	ATitle_GMB();

	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	TObjectPtr<class USoundBase> TitleBGM;
};
