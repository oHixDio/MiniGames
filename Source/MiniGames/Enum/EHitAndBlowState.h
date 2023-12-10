// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHitAndBlowState : uint8
{
	NONE,
	BEFORE_PLAY,
	PLAY,
	AFTER_PLAY,
	RESULT,
	RESULT_IN,
	PIN_SPAWN,
};
