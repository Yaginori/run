#pragma once
class Floor :public GameObject
{
public:
	Floor(const VECTOR& in_pos, // �R���X�g���N�^
		const int in_modelHandle,
		const bool in_isColijonFlag);

	void Draw();
};

