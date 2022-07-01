//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "DxLib.h"
#include "GameObject.h"


// ��Q���̐�.//���Ƃł܂Ƃ߂Ƃ��Ă�
#define LINE_ENEMY_COL 30
#define LINE_ENEMY_RAW 3

#define ENEMY_SPACE_D 500.0f // ��Q���̏c�Ԋu.
#define ENEMY_SPACE_W 550.0f // ��Q���̉��Ԋu.


class Enemy final: public GameObject
{
public:
	Enemy();				// �R���X�g���N�^.
	~Enemy();				// �f�X�g���N�^.

	void Update(float deltaTime);  // �X�V.
	void Draw();			       // �`��.

	void CreateEnemys();			// ��Q������.

	void DestrooyEnemys();		// ��Q���폜.

	GameObject* GetStage(int raw, int col);

	VECTOR scale;

private:
	GameObject*enemys[LINE_ENEMY_RAW][LINE_ENEMY_COL];

	class AnimationController* mAnimControl;

	int     animHandles[4];  // �A�j���[�V�����p�̃��f���n���h��
	float   animFrames[4];    // �A�j���[�V�����Đ�����
	int     animAttachIndices[4]; // �A�j���[�V�����̃A�^�b�`�ԍ�
	int     animIndex;
	float   animTime;
	int tekusutya;
	int texIndex;
	int m_enemyModelHandle;


};

#endif // _ENEMY_H_