//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DxLib.h"
#include "GameObject.h"

#define HIT_TIME 5
#define PLAYER_MODEL_SCALE 0.8f


class Player final
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	// 衝突処理.
	void OnHitObstruct(GameObject& obstruct);


	//当たり判定をfalseに戻すだけ
	static bool hitFlag;
	static void ResetHitFlag() { hitFlag = false; }


	void Update(float deltaTime);  // 更新.
	void Draw();			           // 描画.

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

	// あたり判定半径の取得.
	float GetHitRadius() { return hitRadius; }

	// モデルハンドルの取得.
	int Getm_modelHandle() { return m_modelHandle; }


private:

	class AnimationController* mAnimControl;

	int     animHandles[4];  // アニメーション用のモデルハンドル
	float   animFrames[4];    // アニメーション再生時間
	int     animAttachIndices[4]; // アニメーションのアタッチ番号
	int     animIndex;
	float   animTime;
	int tekusutya;
	int texIndex;


	VECTOR	velocity;		// 移動力.
	static const float COLIDE_DECEL_FAC;


	VECTOR pos;
	float hitRadius;
	float m_hitTime;			//無敵時間(よろけアニメーションが終わるまで）
	int m_modelHandle;

	bool  m_jumpFlag;		//	ジャンプ中かどうかを判定する
	float m_yTemp;			//　ジャンプ中のy格納変数
	float m_yPrev;			//　ジャンプ中のy格納変数
	float m_yOrigin;		//  ジャンプ前の座標

	float m_jumpPower;		//  ジュンプする力
	float m_gravity;        //  重力
};

#endif // _PLAYER_H_