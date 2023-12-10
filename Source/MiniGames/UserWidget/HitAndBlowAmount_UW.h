// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "HitAndBlowAmount_UW.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UHitAndBlowAmount_UW : public UMyUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> HitAmountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> BlowAmountText;


protected:
	void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetAmount(int HitAmount, int BlowAmount);
	
};
