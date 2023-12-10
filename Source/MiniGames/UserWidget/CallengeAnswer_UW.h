// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "CallengeAnswer_UW.generated.h"

/**
 * 
 */
UCLASS()
class UCallengeAnswer_UW : public UMyUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> OkeyText;
};
