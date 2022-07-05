#pragma once
class Model
{
public:
	Model();            // コンストラクタ
	~Model();           // デストラクタ

	void LoadModel(const TCHAR* in_modelFile);        // モデルの読み込み
	void Draw();        // モデルの描画
	void SetPos(const VECTOR &in_pos);      // モデルのポジション設定

private:
	int m_modelHandle;  // モデルハンドル

};

