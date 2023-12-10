// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiniGamesGameModeBase.h"
#include "PlayerController/MyPlayerController.h"
#include "Actor/MyActor.h"
#include "Component/InterpToMover.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h" // �ǉ�


// //////////////////// Engine�Œ񋟂���Ă��郁�\�b�h��override�Q //////////////////// //

AMiniGamesGameModeBase::AMiniGamesGameModeBase()
	:Super()
{
}

void AMiniGamesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void AMiniGamesGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// //////////////////// �p�x�������������܂Ƃ߂����\�b�h�Q //////////////////// //

void AMiniGamesGameModeBase::AddInputMap(APlayerController* PlayerController, UInputMappingContext* InputMap, int32 Priority)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMap, Priority);
	}
}

void AMiniGamesGameModeBase::RemoveInputMap(APlayerController* PlayerController, UInputMappingContext* InputMap)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(InputMap);
	}
}

void AMiniGamesGameModeBase::MoveActor(AMyActor* Actor, FVector MoveOffset, float MoveTime)
{
	// UInterpToMover��������Ȃ������瑁�����^�[������
	UInterpToMover* Mover = Cast<UInterpToMover>(Actor->GetComponentByClass(UInterpToMover::StaticClass()));
	if (Mover == nullptr)
	{
		return;
	}
	
	Mover->Set(MoveOffset, MoveTime);
	Mover->SetShouldMove(true);
	Actor->SetIsMove(true);
}


// //////////////////// ���Menu��Q�[���J�n�A�I�����ɌĂ΂�郁�\�b�h�Q //////////////////// //

void AMiniGamesGameModeBase::OpenLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void AMiniGamesGameModeBase::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

