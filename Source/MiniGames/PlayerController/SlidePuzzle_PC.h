// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "SlidePuzzle_PC.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API ASlidePuzzle_PC : public AMyPlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputMappingContext")
	TObjectPtr<class UInputMappingContext> DefaultIMC{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToDone{ nullptr };

public:
	ASlidePuzzle_PC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void test();
	
};
