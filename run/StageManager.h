//-----------------------------------------------------------------------------
// @brief  ��Q���}�l�[�W���[.
//-----------------------------------------------------------------------------
#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

// ��Q���̐�.
#define LINE_STAGE_COL 30
#define LINE_STAGE_RAW 3

#define STAGE_SPACE_D 100.0f // ��Q���̏c�Ԋu.
#define STAGE_SPACE_W 550.0f // ��Q���̉��Ԋu.

#include "DxLib.h"
#include "GameObject.h"
#include <vector>

class StageManager final:public GameObject
{
public:
	StageManager();				    // �R���X�g���N�^.
	~StageManager();				// �f�X�g���N�^.

	void CreateStages();			// ��Q������.
	void DestroyStages();		    // ��Q���폜.

	void Update(float deltaTime)override;  // �X�V.
	void Draw();					// �`��.

	// �w��ԍ��̏�Q�����擾.
	GameObject* GetStage(int raw, int col);

	VECTOR scale;

	GameObject* Obstructs[LINE_STAGE_RAW][LINE_STAGE_COL];

//�Q�l
	//�C���X�^���X�̍쐬
	static void CreateInstance();

	static void DeleteInstance();




private:

	int floatModelSourceHandle;		// ���V���f���̑�{�̃n���h��.
	int staticModelSourceHandle;	// �Î~���f���̑�{�̃n���h��.


	// �Q�l
	// StageManager�̎��́i�A�v�����ɗB�ꑶ�݁j
	static StageManager* mManager;

	// �S�ẴI�u�W�F�N�g���i�[����R���e�i
	std::vector<GameObject*>mObject;





};

#endif // _STAGE_MANAGER_H_