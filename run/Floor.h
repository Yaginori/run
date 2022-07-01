#pragma once
class Floor :public GameObject
{
public:
	Floor(const VECTOR& in_pos, // コンストラクタ
		const int in_modelHandle,
		const bool in_isColijonFlag);

	void Draw();
};

