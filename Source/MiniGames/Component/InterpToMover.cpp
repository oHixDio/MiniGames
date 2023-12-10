// Fill out your copyright notice in the Description page of Project Settings.


#include "InterpToMover.h"
#include "../MiniGamesGameModeBase.h"
#include <MiniGames/Actor/MyActor.h>

// Sets default values for this component's properties
UInterpToMover::UInterpToMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UInterpToMover::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UInterpToMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bShouldMove) { return; }

	// 現在の位置を取得
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	// 移動する位置を取得
	FVector TargetLocation = OriginalLocation + MoveOffset;

	// 目標地点に達したときTickを止める
	if (TargetLocation == CurrentLocation)
	{
		SetShouldMove(false);
		AMyActor* Owner = Cast<AMyActor>(GetOwner());
		Owner->SetIsMove(false);
	}

	// 移動距離を移動時間で割ったのが移動速度となる
	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

	// 現在位置から目標地点まで、指定時間で移動させる関数
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	// 計算で得たロケーションをセットする
	GetOwner()->SetActorLocation(NewLocation);
}

void UInterpToMover::Set(FVector NewMoveOffset, float NewMoveTime)
{
	MoveOffset = NewMoveOffset;
	MoveTime = NewMoveTime;
	OriginalLocation = GetOwner()->GetActorLocation();
}

