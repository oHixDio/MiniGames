// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "Title_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API ATitle_HUD : public AMyHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> TitleUIClass;

	TObjectPtr<class UUserWidget> TitleUI;

public:
	virtual void BeginPlay() override;

public:
	const TObjectPtr<class UUserWidget> GetTitleUI() const { return TitleUI; }
	
public:
	virtual void Setup() override;
};
