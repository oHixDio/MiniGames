// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPinType : uint8
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	YELLOW = 3,
	PURPLE = 4,
	BLACK = 5,
	// RED~BLACK‚Ü‚Å‚ÌƒJƒEƒ“ƒg
	COUNT = 6,

	HIT = 6,
	BLOW = 7,

	UNKNOWN = 8,
};
