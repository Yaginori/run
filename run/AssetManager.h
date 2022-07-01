#pragma once
#include <DxLib.h>
#include <unordered_map>
//#include <atlstr.h>
#include <string>

class AssetManager
{
public:
	static AssetManager& GetInstance()
	{
		static AssetManager inst;
		return inst;
	}

	~AssetManager();
	int  GetMesh(std::string meshFileName);           // �t�@�C�����烁�b�V���i���f���n���h���j�𓾂�
	int  GetAnimation(std::string animationFileName); // �t�@�C������A�j���[�V�����n���h���𓾂�
	void RemoveMesh(int meshID);                      // ���b�V��ID(���f���n���h��)�̓o�^�������J������
	void RemoveAll();                                 // ���ׂĉ������

private:
	AssetManager();                                   // �V���O���g��

	std::unordered_map<std::string, int> mMeshMap;    // ���b�V�����{�i������͌��{�Ƃ��ĕۑ������s���ADuplicate���ꂽ���̂�Ԃ��j
	std::unordered_map<std::string, int> mAnimMap;    // �A�j���[�V�������{�i������͕Ԃ�)
	std::vector<int> mDuplicatesMesh;                 // ���b�V�����R�s�[�������́i��������g�p����j
};

// GetInstance�̏ȗ��`
#define ASSET AssetManager::GetInstance()
