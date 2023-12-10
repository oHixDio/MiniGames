// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGames/MiniGamesGameModeBase.h"
#include "SlidePuzzle_GMB.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API ASlidePuzzle_GMB : public AMiniGamesGameModeBase
{
	GENERATED_BODY()
	
public:
	ASlidePuzzle_GMB();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:

};
