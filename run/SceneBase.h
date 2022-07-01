#pragma once
class SceneBase
{
public:
	// シーンの種類タグ
	enum class Scene :unsigned char
	{
		e_init,
		e_title,
		e_game,
	};

	SceneBase(Scene in_nowScene); // コンストラクタ
	~SceneBase();				  // デストラクタ

	/// <returns>現在のシーンのポインタ</returns>
	virtual SceneBase* Update(float _deltaTime) = 0; // 制御
	virtual void Draw() = 0; // 描画

	// 現在のシーンタグ
	static Scene nowScene;

};

