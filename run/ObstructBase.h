//-----------------------------------------------------------------------------
// @brief  障害物基底クラス.
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_BASE_H_
#define _OBSTRUCT_BASE_H_

#include "DxLib.h"

class ObstructBase
{
public:
	ObstructBase(int sourceModelHandle);	// コンストラクタ.
	virtual ~ObstructBase();				// デストラクタ.

	virtual void Update() = 0;				// 更新.
	virtual void Draw();					// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() { return modelHandle; }

protected:
};

#endif // _OBSTACLE_BASE_H_