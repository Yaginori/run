//-----------------------------------------------------------------------------
// @brief  ��Q���F����
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_STATIC_H_
#define _OBSTRUCT_STATIC_H_

#include "GameObject.h"

// ��Q���̐�.//���Ƃł܂Ƃ߂Ƃ��Ă�
#define LINE_STAGE_COL 30
#define LINE_STAGE_RAW 3

#define STAGE_SPACE_D 500.0f // ��Q���̏c�Ԋu.

class ObstructStatic : public GameObject
{
public:
	ObstructStatic(int sourcem_modelHandle,VECTOR in_setPos);
	//ObstructStatic(int sourcem_modelHandle, VECTOR _scale);

	VECTOR scale;

	// �R���X�g���N�^.
	virtual ~ObstructStatic();				// �f�X�g���N�^.

	void Update(float deltaTime)override;		// �X�V.


};

#endif // _OBSTACLE_BASE_H_

