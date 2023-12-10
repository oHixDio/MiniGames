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

	// ���݂̈ʒu���擾
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	// �ړ�����ʒu���擾
	FVector TargetLocation = OriginalLocation + MoveOffset;

	// �ڕW�n�_�ɒB�����Ƃ�Tick���~�߂�
	if (TargetLocation == CurrentLocation)
	{
		SetShouldMove(false);
		AMyActor* Owner = Cast<AMyActor>(GetOwner());
		Owner->SetIsMove(false);
	}

	// �ړ��������ړ����ԂŊ������̂��ړ����x�ƂȂ�
	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

	// ���݈ʒu����ڕW�n�_�܂ŁA�w�莞�Ԃňړ�������֐�
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	// �v�Z�œ������P�[�V�������Z�b�g����
	GetOwner()->SetActorLocation(NewLocation);
}

void UInterpToMover::Set(FVector NewMoveOffset, float NewMoveTime)
{
	MoveOffset = NewMoveOffset;
	MoveTime = NewMoveTime;
	OriginalLocation = GetOwner()->GetActorLocation();
}

