// Fill out your copyright notice in the Description page of Project Settings.


#include "Pin.h"
#include "Components/WidgetComponent.h"
#include "Materials/MaterialInstance.h"
#include "../Component/InterpToMover.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>

APin::APin()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root����
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	PinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pin"));
	PinMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	InterpToMoverComp = CreateDefaultSubobject<UInterpToMover>(TEXT("InterpToMoverComp"));

	QuestionMark = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionMark"));
	QuestionMark->AttachToComponent(PinMesh, FAttachmentTransformRules::KeepRelativeTransform);

	
}

void APin::BeginPlay()
{
	Super::BeginPlay();

	// �͂Ăȃ}�[�N�͒ʏ�����Ă���
	ComponentSetHidden(QuestionMark, true);

	PinMesh->SetMaterial(0, MaterialList[(int)MyType]);
	CurrentSE = PinSE;
}

void APin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void APin::Setup(EPinType Type)
{
	// �^�C�v��ݒ�	
	MyType = Type;

	if (MyType == EPinType::HIT || MyType == EPinType::BLOW)
	{
		SetActorScale3D(FVector(MiniSize));
	}
	else if (MyType == EPinType::UNKNOWN)
	{
		SetActorScale3D(FVector(MaxSize));
		// Unknown�͂͂Ăȃ}�[�N���o��
		ComponentSetHidden(QuestionMark, false);
	}
	else
	{
		SetActorScale3D(FVector(DefaultSize));
	}

	PinMesh->SetMaterial(0, MaterialList[(int)MyType]);

	// �ړ��A�j���[�V���������s
	{
		SetActorLocation(GetActorLocation() + AnimationOffset);

		InterpToMoverComp->Set(-AnimationOffset, MoveTime);

		InterpToMoverComp->SetShouldMove(true);

	}
	PlaySE();
}

// MoveTime��ɍĐ������悤�ɂȂ��Ă���
void APin::PlaySE()
{
	CurrentSE = PinSE;

	if (MyType == EPinType::HIT)
	{
		CurrentSE = HitSE;
	}
	else if (MyType == EPinType::BLOW)
	{
		CurrentSE = BlowSE;
	}

	FTimerHandle SEHandle;
	// MyActor�Ƀ��\�b�h�������Ă����A�R���|�[�l���g�ŉ���炵�Ă��ǂ�
	GetWorldTimerManager().SetTimer(
		SEHandle,
		[&]()
		{
			// SE Play
			UGameplayStatics::SpawnSound2D(GetWorld(), CurrentSE, 1.0f, 1.0f, 0, nullptr, false, false);
		},
		MoveTime,
		false
	);
}
