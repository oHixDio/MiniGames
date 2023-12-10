// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "QuestionMark_UW.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UQuestionMark_UW : public UMyUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuestionText;
	
protected:
	virtual void NativeConstruct() override;
};
