#pragma once
#include <DxLib.h>

class GameObject
{

public:
	GameObject(int sourcem_modelHandle,VECTOR in_setPos);
	GameObject();
	~GameObject();

	virtual void Update(float deltaTime)/* = 0*/;  // �X�V.
	virtual void Draw();			           // �`��.

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR set) { m_pos = set; }

	// �����蔻�蔼�a�̎擾.
	float GetHitRadius() { return hitRadius; }

	//// ���f���n���h���̎擾.
	//int Getm_modelHandle() { return m_modelHandle; }


protected:
	VECTOR m_pos;
	float hitRadius;
	int m_modelHandle;

};

