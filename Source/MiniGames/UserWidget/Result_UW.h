// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include <InputActionValue.h>
#include "Result_UW.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UResult_UW : public UMyUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackGround;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResultText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> DetailText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> RestartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> RestartText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> BackToTitleButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> BackToTitleText;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor White = FLinearColor(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Green = FLinearColor(0, 1, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Red = FLinearColor(1, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spund|SE")
	TObjectPtr<class USoundBase> SelectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spund|SE")
	TObjectPtr<class USoundBase> DoneSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float DoneRate{ 1 };

	UPROPERTY(VisibleAnywhere)
	bool bIsDone{ false };


private:
	enum class ESelect
	{
		RESTART,
		BACK_TO_TITLE,
	};

	ESelect Select{ ESelect::RESTART };

protected:
	void NativeConstruct() override;

public:

	void OnButton();

	void OnSelect(const FInputActionValue& Value);

	void ResetColorToButton();

	void SetColorButton();

	UFUNCTION(BlueprintCallable)
	void SetResultText(bool bIsClear);
};
