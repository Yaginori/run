#pragma once
class SceneBase
{
public:
	// �V�[���̎�ރ^�O
	enum class Scene :unsigned char
	{
		e_init,
		e_title,
		e_game,
	};

	SceneBase(Scene in_nowScene); // �R���X�g���N�^
	~SceneBase();				  // �f�X�g���N�^

	/// <returns>���݂̃V�[���̃|�C���^</returns>
	virtual SceneBase* Update(float _deltaTime) = 0; // ����
	virtual void Draw() = 0; // �`��

	// ���݂̃V�[���^�O
	static Scene nowScene;

};

