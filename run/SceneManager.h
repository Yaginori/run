#pragma once
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Update(float _deltaTime);       // ����
	void Draw();         // �`��
	void Sound();        // ��

	void SetScene(SceneBase* in_scene);  // �V�[�����Z�b�g

private:
	SceneBase* m_nowScene;

};

