//-----------------------------------------------------------------------------
// @brief  ��Q���}�l�[�W���[.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_MANAGER_H_
#define _OBSTRUCT_MANAGER_H_

class ObstructBase;

// ��Q���̐�.
#define LINE_OBSTRUCT_COL 7
#define LINE_OBSTRUCT_RAW 30

#define OBSTRUCT_SPACE_D 20.0f // ��Q���̏c�Ԋu.
#define OBSTRUCT_SPACE_W 20.0f // ��Q���̉��Ԋu.

class ObstructManager final
{
public:
	ObstructManager();				// �R���X�g���N�^.
	~ObstructManager();				// �f�X�g���N�^.

	void CreateObstructs();			// ��Q������.
	void DestroyObstructs();		// ��Q���폜.

	void Update();					// �X�V.
	void Draw();					// �`��.

	// �w��ԍ��̏�Q�����擾.
	ObstructBase* GetObstruct(int raw, int col);

private:
	ObstructBase* obstructs[LINE_OBSTRUCT_RAW][LINE_OBSTRUCT_COL];

	int floatModelSourceHandle;		// ���V���f���̑�{�̃n���h��.
	int staticModelSourceHandle;	// �Î~���f���̑�{�̃n���h��.
};

#endif // _OBSTRUCT_MANAGER_H_