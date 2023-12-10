// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "FixedCamera.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API AFixedCamera : public AMyActor
{
	GENERATED_BODY()
	
public:
	
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInterpToMover* InterpToMoverComp{ nullptr };
	
public:
	AFixedCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
