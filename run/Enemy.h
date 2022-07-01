//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "DxLib.h"
#include "GameObject.h"


// 障害物の数.//あとでまとめといてね
#define LINE_ENEMY_COL 30
#define LINE_ENEMY_RAW 3

#define ENEMY_SPACE_D 500.0f // 障害物の縦間隔.
#define ENEMY_SPACE_W 550.0f // 障害物の横間隔.


class Enemy final: public GameObject
{
public:
	Enemy();				// コンストラクタ.
	~Enemy();				// デストラクタ.

	void Update(float deltaTime);  // 更新.
	void Draw();			       // 描画.

	void CreateEnemys();			// 障害物生成.

	void DestrooyEnemys();		// 障害物削除.

	GameObject* GetStage(int raw, int col);

	VECTOR scale;

private:
	GameObject*enemys[LINE_ENEMY_RAW][LINE_ENEMY_COL];

	class AnimationController* mAnimControl;

	int     animHandles[4];  // アニメーション用のモデルハンドル
	float   animFrames[4];    // アニメーション再生時間
	int     animAttachIndices[4]; // アニメーションのアタッチ番号
	int     animIndex;
	float   animTime;
	int tekusutya;
	int texIndex;
	int m_enemyModelHandle;


};

#endif // _ENEMY_H_