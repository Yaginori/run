#pragma once
class Wall :public GameObject
{
public:
	Wall(const VECTOR& in_pos, // �R���X�g���N�^
		const int in_modelHandle,
		const bool in_isColijonFlag);
};

