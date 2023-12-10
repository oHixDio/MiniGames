// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "InitAnimText_UW.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UInitAnimText_UW : public UMyUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;


protected:
	UPROPERTY(EditAnywhere)
	FText DefaultText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InitAnimText;

};
