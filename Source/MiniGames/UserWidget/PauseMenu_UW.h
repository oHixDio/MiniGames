// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include <InputActionValue.h>
#include "PauseMenu_UW.generated.h"


/**
 * 
 */
UCLASS()
class MINIGAMES_API UPauseMenu_UW : public UMyUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResumeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> RestartText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> BackToTitleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> RestartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> BackToTitleButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor White = FLinearColor(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Green = FLinearColor(0, 1, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spund|SE")
	TObjectPtr<class USoundBase> SelectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spund|SE")
	TObjectPtr<class USoundBase> DoneSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spund|SE")
	TObjectPtr<class USoundBase> PauseSE;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Timers|float")
	float DoneRate{ 1 };

	UPROPERTY(VisibleAnywhere)
	bool bIsDone{ false };

	bool bShuldCntTimer{ false };
	float DoneTimer{ 1 };

private:
	enum class ESelect
	{
		RESUME,
		RESTART,
		BACK_TO_TITLE,
	};

	ESelect Select{ ESelect::RESUME };

protected:
	virtual void NativeConstruct() override;

public:
	// Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	
	void OnButton();

	void OnSelect(const FInputActionValue& Value);

	void OnCancel();

	void ResetColorToButton();

	void SetColorButton();

};
