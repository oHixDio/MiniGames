// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_GMB.h"
#include "EnhancedInputSubsystems.h" // ’Ç‰Á
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"

ATitle_GMB::ATitle_GMB()
	:Super()
{
}

void ATitle_GMB::BeginPlay()
{
	Super::BeginPlay();

	if (TitleBGM != nullptr)
	{
		UGameplayStatics::SpawnSound2D(GetWorld(), TitleBGM, 1.0f, 1.0f, 0.0f, nullptr, false, false);
	}
}
