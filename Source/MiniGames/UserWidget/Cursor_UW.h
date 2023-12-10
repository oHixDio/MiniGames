// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "Cursor_UW.generated.h"


/**
 * 
 */
UCLASS()
class MINIGAMES_API UCursor_UW : public UMyUserWidget
{
	GENERATED_BODY()

	
protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* MainImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* SubImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* ColTopImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* ColBottomImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* RowLeftImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* RowRightImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* CenterTopImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* CenterBottomImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* CenterLeftImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* CenterRightImage;


public:
	UCursor_UW();

};
