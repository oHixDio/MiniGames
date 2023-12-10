// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "InputActionValue.h" // ’Ç‰Á
#include "Title_PC.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API ATitle_PC : public AMyPlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputMappingContext")
	TObjectPtr<class UInputMappingContext> DefaultIMC{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToDone{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToCancel{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToSelectX{ nullptr };

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|InputActions")
	TObjectPtr<class UInputAction> InputToSelectY{ nullptr };

	// UPROPERTY‚Í‚Â‚¯‚ç‚ê‚È‚¢
	TArray<FInputBindingHandle> BindingActionList;


public:

	virtual void BeginPlay() override;


public:

	void BindTitleAction();
};
