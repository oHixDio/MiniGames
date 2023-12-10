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

	// Root生成
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

	// はてなマークは通常消しておく
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
	// タイプを設定	
	MyType = Type;

	if (MyType == EPinType::HIT || MyType == EPinType::BLOW)
	{
		SetActorScale3D(FVector(MiniSize));
	}
	else if (MyType == EPinType::UNKNOWN)
	{
		SetActorScale3D(FVector(MaxSize));
		// Unknownははてなマークを出す
		ComponentSetHidden(QuestionMark, false);
	}
	else
	{
		SetActorScale3D(FVector(DefaultSize));
	}

	PinMesh->SetMaterial(0, MaterialList[(int)MyType]);

	// 移動アニメーションを実行
	{
		SetActorLocation(GetActorLocation() + AnimationOffset);

		InterpToMoverComp->Set(-AnimationOffset, MoveTime);

		InterpToMoverComp->SetShouldMove(true);

	}
	PlaySE();
}

// MoveTime後に再生されるようになっている
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
	// MyActorにメソッドを持っていき、コンポーネントで音を鳴らしても良い
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
