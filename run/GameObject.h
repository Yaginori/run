#pragma once
#include <DxLib.h>

class GameObject
{

public:
	GameObject(int sourcem_modelHandle,VECTOR in_setPos);
	GameObject();
	~GameObject();

	virtual void Update(float deltaTime)/* = 0*/;  // 更新.
	virtual void Draw();			           // 描画.

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR set) { m_pos = set; }

	// あたり判定半径の取得.
	float GetHitRadius() { return hitRadius; }

	//// モデルハンドルの取得.
	//int Getm_modelHandle() { return m_modelHandle; }


protected:
	VECTOR m_pos;
	float hitRadius;
	int m_modelHandle;

};

