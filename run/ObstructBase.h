//-----------------------------------------------------------------------------
// @brief  ��Q�����N���X.
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_BASE_H_
#define _OBSTRUCT_BASE_H_

#include "DxLib.h"

class ObstructBase
{
public:
	ObstructBase(int sourceModelHandle);	// �R���X�g���N�^.
	virtual ~ObstructBase();				// �f�X�g���N�^.

	virtual void Update() = 0;				// �X�V.
	virtual void Draw();					// �`��.

	// ���f���n���h���̎擾.
	int GetModelHandle() { return modelHandle; }

protected:
};

#endif // _OBSTACLE_BASE_H_