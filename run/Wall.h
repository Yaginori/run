#pragma once
class Wall :public GameObject
{
public:
	Wall(const VECTOR& in_pos, // コンストラクタ
		const int in_modelHandle,
		const bool in_isColijonFlag);
};

