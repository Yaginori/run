#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Update(float _deltaTime);       // 制御
	void Draw();         // 描画
	void Sound();        // 音

	void SetScene(SceneBase* in_scene);  // シーンをセット

private:
	SceneBase* m_nowScene;

};

