// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	AMyGameStateBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
