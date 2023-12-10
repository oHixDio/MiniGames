// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include <InputActionValue.h>
#include "Title_UW.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UTitle_UW : public UMyUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TitleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> HitAndBlowText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> SlidePuzzleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuitText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> HitAndBlowButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> SlidePuzzleButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SE")
	TObjectPtr<class USoundBase> SelectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SE")
	TObjectPtr<class USoundBase> DoneSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor White = FLinearColor(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Green = FLinearColor(0, 1, 0);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float DoneRate{ 1 };

	UPROPERTY(VisibleAnywhere)
	bool bIsDone{ false };

private:
	enum class ESelect
	{
		HIT_AND_BLOW,
		SLIDE_PUZZLE,
		QUIT,
	};

	ESelect Select{ ESelect::HIT_AND_BLOW };

protected:
	void NativeConstruct() override;

public:
	UTitle_UW();

	void OnButton();

	void OnSelect(const FInputActionValue& Value);

	void OnCancel();

	void ResetColorToButton();

	void SetColorButton();
};
