// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedCamera.h"
#include "Camera/CameraComponent.h"
#include "../Component/InterpToMover.h"

AFixedCamera::AFixedCamera()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// Rootê∂ê¨
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	InterpToMoverComp = CreateDefaultSubobject<UInterpToMover>(TEXT("InterpToMoverComp"));

}

void AFixedCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AFixedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



