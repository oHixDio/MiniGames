// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UInterpToMover;


UCLASS(Abstract)
class MINIGAMES_API AMyActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	bool bIsMove{ false };


public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	const bool GetIsMove() const { return bIsMove; }

	void SetIsMove(const bool IsMove) { bIsMove = IsMove; }


public:
	void ComponentSetHidden(TObjectPtr<USceneComponent> Component, bool bIsHidden);

};
