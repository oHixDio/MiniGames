// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "UI|My")
	TSubclassOf<class UUserWidget> PauseMenuUIClass;

	UPROPERTY(VisibleAnywhere, Category = "UI|My")
	TObjectPtr<class UUserWidget> PauseUI;

	UPROPERTY(EditAnywhere, Category = "UI|My")
	TSubclassOf<class UUserWidget> LoadingUIClass;

	UPROPERTY(VisibleAnywhere, Category = "UI|My")
	TObjectPtr<class UUserWidget> LoadingUI;

public:

	AMyHUD();

	virtual void BeginPlay() override;

public:
	const TObjectPtr<class UUserWidget> GetPauseUI() const;

	const TObjectPtr<class UUserWidget> GetLoadingUI() const;

public:
	virtual void Setup();

	virtual TObjectPtr<class UUserWidget> CreateUI(TSubclassOf<UUserWidget> WidgetClass);

	virtual void AddUI(TObjectPtr<class UUserWidget> Widget);

	virtual void RemoveUI(TObjectPtr<class UUserWidget> Widget);

};
