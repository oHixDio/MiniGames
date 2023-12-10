// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidePuzzle_PC.h"
#include "InputAction.h" // ’Ç‰Á
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h" // ’Ç‰Á
#include "EnhancedInputSubsystems.h" // ’Ç‰Á
#include "Kismet/GameplayStatics.h"

ASlidePuzzle_PC::ASlidePuzzle_PC()
	:Super()
{
}

void ASlidePuzzle_PC::BeginPlay()
{
	Super::BeginPlay();

	// Pause‚Ì‚Ý‚Å‚«‚é
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputToDone, ETriggerEvent::Triggered, this, &ASlidePuzzle_PC::test);
	}
	EnableInput(this);UE_LOG(LogTemp, Warning, TEXT("Hi"));
}

void ASlidePuzzle_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlidePuzzle_PC::test()
{
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}

