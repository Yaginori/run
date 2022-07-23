//-----------------------------------------------------------------------------
// @brief  障害物：建物
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_STATIC_H_
#define _OBSTRUCT_STATIC_H_

#include "GameObject.h"

// 障害物の数.//あとでまとめといてね
#define LINE_STAGE_COL 30
#define LINE_STAGE_RAW 3

#define STAGE_SPACE_D 500.0f // 障害物の縦間隔.

class ObstructStatic : public GameObject
{
public:
	ObstructStatic(int sourcem_modelHandle,VECTOR in_setPos);
	//ObstructStatic(int sourcem_modelHandle, VECTOR _scale);

	VECTOR scale;

	// コンストラクタ.
	virtual ~ObstructStatic();				// デストラクタ.

	void Update(float deltaTime)override;		// 更新.


};

#endif // _OBSTACLE_BASE_H_

