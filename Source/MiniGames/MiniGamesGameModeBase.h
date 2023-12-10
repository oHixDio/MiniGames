// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGamesGameModeBase.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MINIGAMES_API AMiniGamesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	/*
	* Engine�Œ񋟂���Ă��郁�\�b�h��override�Q
	*/
public:
	AMiniGamesGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/*
	* �p�x�������������܂Ƃ߂����\�b�h�Q
	*/
public:
	// InputMappingContect�����t����
	void AddInputMap(APlayerController* PlayerController, class UInputMappingContext* InputMap, int32 Priority = 0);

	// InputMappingContect�����O��
	void RemoveInputMap(APlayerController* PlayerController, class UInputMappingContext* InputMap);

	// Actor��InterpToMove�����郁�\�b�h
	UFUNCTION(BlueprintCallable)
	void MoveActor(class AMyActor* Actor, FVector MoveOffset, float MoveTime);

	/*
	* ���Menu��Q�[���J�n�A�I�����ɌĂ΂�郁�\�b�h�Q
	*/
public:
	void OpenLevel(FName LevelName);

	void QuitGame();
	

	// �������z�֐��ɂ�����@
	// ���������߂�l�����̏ꍇ�A�N���X��::�֐���,
	// �߂�l����̏ꍇ���L�̂悤�ȋL�q������
	//virtual AActor* FixedCameraSponner() PURE_VIRTUAL(AMiniGamesGameModeBase::FixedCameraSponner, return 0;);
	
	/*
	* Controller InputMappingContext�̊���	// OK
	* Controller���͂̉\�ƕs�\			// OK
	* Cursor�̕\����\��						// OK
	* �^�C�g���̍쐬							// OK
	* �^�C�g������C���Q�[����					// OK
	* �|�[�Y�̍쐬							// OK
	* �C���Q�[������^�C�g����					// OK
	* ���X�^�[�g���x��						// OK
	* �Q�[�����U���g�̕\��
	* Cursor�̈ړ�
	* Turn�̕ύX
	* �s���N���X�쐬�A�s�������A�s���}�e���A���ݒ�A�s���A�j���[�V����
	* �s�����S�������ꂽ�Ƃ��̏���
	* �������킹�t���[�̍쐬
	* ���������Ƃ��̏����쐬
	* ���������̍쐬
	* SE�̑}��
	* �G�t�F�N�g�̑}��
	* -------------------------------------------------------------------------11���I��
	*
	* �v���C���[�l���̕ύX���\�ɂ���
	* ����ɔ���HitAndBlow�̉���
	* SlidePuzzle�̃{�[�h�쐬
	* Cursor�쐬
	* Cursor���̃R���g���[�����瓮������悤�ɂ���
	* Piece�̍쐬
	* Piece�̈ړ��V�X�e���쐬
	* Spline�̍쐬
	* MoveObj�̍쐬
	* MoveObj�̈ړ��V�X�e���쐬
	* ���s�t���[�̍쐬
	* Dia�̍쐬
	* Dia�̐���
	* Dia�̃|�C���g�쐬
	* --------------------------------------------------------------------------12���I��
	*
	*
	*
	*
	*/


};
