#pragma once
class Model
{
public:
	Model();            // �R���X�g���N�^
	~Model();           // �f�X�g���N�^

	void LoadModel(const TCHAR* in_modelFile);        // ���f���̓ǂݍ���
	void Draw();        // ���f���̕`��
	void SetPos(const VECTOR &in_pos);      // ���f���̃|�W�V�����ݒ�

private:
	int m_modelHandle;  // ���f���n���h��

};

