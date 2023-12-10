// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InterpToMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIGAMES_API UInterpToMover : public UActorComponent
{
	GENERATED_BODY()

	
private:
	UPROPERTY(EditAnywhere)
	float MoveTime{ 0 };

	UPROPERTY(EditAnywhere)
	FVector MoveOffset{ FVector(0) };

	UPROPERTY(VisibleAnywhere)
	bool bShouldMove{ false };

	FVector OriginalLocation;

public:	
	// Sets default values for this component's properties
	UInterpToMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetShouldMove(bool bInShouldMove) 
	{
		OriginalLocation = GetOwner()->GetActorLocation();
		bShouldMove = bInShouldMove; 
	}

	const float GetMoveTime() const { return MoveTime; }

	void Set(FVector NewMoveOffset, float NewMoveTime);
};
