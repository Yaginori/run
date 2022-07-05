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
		e_result
	};

	SceneBase(Scene in_nowScene); // �R���X�g���N�^
	~SceneBase();				  // �f�X�g���N�^

	/// <returns>���݂̃V�[���̃|�C���^</returns>
	virtual SceneBase* Update(float _deltaTime) = 0; // ����
	virtual void Draw(); // �`��
	virtual void Load() = 0; // �f�[�^�̓ǂݍ���

	// ���݂̃V�[���^�O
	static Scene nowScene;

protected:
	int m_modelHandle;

};

