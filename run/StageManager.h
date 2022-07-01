//-----------------------------------------------------------------------------
// @brief  障害物マネージャー.
//-----------------------------------------------------------------------------
#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

// 障害物の数.
#define LINE_STAGE_COL 30
#define LINE_STAGE_RAW 3

#define STAGE_SPACE_D 100.0f // 障害物の縦間隔.
#define STAGE_SPACE_W 550.0f // 障害物の横間隔.

#include "DxLib.h"
#include "GameObject.h"
#include <vector>

class StageManager final:public GameObject
{
public:
	StageManager();				    // コンストラクタ.
	~StageManager();				// デストラクタ.

	void CreateStages();			// 障害物生成.
	void DestroyStages();		    // 障害物削除.

	void Update(float deltaTime)override;  // 更新.
	void Draw();					// 描画.

	// 指定番号の障害物を取得.
	GameObject* GetStage(int raw, int col);

	VECTOR scale;

	GameObject* Obstructs[LINE_STAGE_RAW][LINE_STAGE_COL];

//参考
	//インスタンスの作成
	static void CreateInstance();

	static void DeleteInstance();




private:

	int floatModelSourceHandle;		// 浮遊モデルの大本のハンドル.
	int staticModelSourceHandle;	// 静止モデルの大本のハンドル.


	// 参考
	// StageManagerの実体（アプリ内に唯一存在）
	static StageManager* mManager;

	// 全てのオブジェクトを格納するコンテナ
	std::vector<GameObject*>mObject;





};

#endif // _STAGE_MANAGER_H_