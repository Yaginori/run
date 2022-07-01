
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
AssetManager::AssetManager()
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
AssetManager::~AssetManager()
{
}

//-----------------------------------------------------------------------------
// @brief  ���b�V���̎擾.
// @param[in] meshFileName �擾���������b�V���t�@�C����.
// @return int ���b�V���̃n���h��.
// 
// @details ���b�V���i���f��)�n���h�����擾����B
// �����t�@�C������2�x�ȏ�w�肵���Ƃ��́A�t�@�C���ǂݍ��݂͍s��ꂸ�Aduplicate���ꂽ�n���h����Ԃ��B
// �t�@�C����������Ȃ��Ƃ���-1��Ԃ�.
//-----------------------------------------------------------------------------
int AssetManager::GetMesh(std::string meshFileName)
{
	int meshId = 0;
	// �A�z�z�񂩂�ȑO�ɓo�^����ĂȂ����𒲂ׂ�
	auto iter = mMeshMap.find(meshFileName);

	// ������Ȃ������ꍇ�͐V�K�Ńt�@�C����ǂݍ��݁A�A�z�z��ɋL�^����
	if (iter == mMeshMap.end())
	{
		meshId = MV1LoadModel(meshFileName.c_str());
		if (meshId == -1)
		{
			return meshId;
		}
		mMeshMap.emplace(meshFileName, meshId); //mMeshMap[meshFileName] = meshId�̂���
	}

	// �V�K�ǂݍ��݂�2��ړǂݍ��݂��Aduplicate�������̂�ԋp����
	// ���b�V�����g���L�����N�^�[�����������ꍇ�ɁA���{���������ƑS�������č��邩��
	// ���b�V���̃R�s�[�폜�p��mDuplicateMesh�ɕۑ�
	meshId = MV1DuplicateModel(mMeshMap[meshFileName]);
	mDuplicatesMesh.push_back(meshId);

	return meshId;
}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V�����̓ǂݍ���.
// @param[in] animationFileName �ǂݍ��݂����A�j���[�V�����t�@�C����.
// @return int �A�j���[�V�����n���h��.
// 
// @details �A�j���[�V�������t�@�C���ǂݍ��݂��A�A�j���[�V�����n���h����Ԃ�
// �����t�@�C������2�x�ȏ�ǂݍ��܂ꂽ�ꍇ�́A�ǂݍ��݂��s�킸�n���h���̂ݕԂ�
// �A�j���[�V������Duplicate����Ȃ��B�t�@�C����������Ȃ��Ƃ���-1��Ԃ�.         
//-----------------------------------------------------------------------------
int AssetManager::GetAnimation(std::string animationFileName)
{
	int animId = 0;
	auto iter = mAnimMap.find(animationFileName);

	// ������Ȃ������ꍇ�͐V�K�ǂݍ��݂��A�A�z�z��ɋL�^����
	if (iter == mAnimMap.end())
	{
		animId = MV1LoadModel(animationFileName.c_str());
		if (animId == -1)
		{
			return animId;
		}
		mAnimMap.emplace(animationFileName, animId);  // mAnimMap[animationFileName] = animId;�̂���
	}

	// �A�j���[�V������ID��Ԃ�
	return mAnimMap[animationFileName];
}

//-----------------------------------------------------------------------------
// @brief  ���b�V���̉��
// @param[in] meshID ������������f���n���h��.
// 
// @details duplicate���ꂽ���f���n���h�����J������
// duplicate���ꂽ���f���n���h���Ȃ̂ŁA�S�������Ă����{�̃��f���n���h���͓����I�Ɏc��         
//-----------------------------------------------------------------------------
void AssetManager::RemoveMesh(int meshID)
{
	// Duplicate�̒��Ń��b�V�����������A�폜
	auto iter = std::find(mDuplicatesMesh.begin(), mDuplicatesMesh.end(), meshID);
	if (iter == mDuplicatesMesh.end())
	{
		return;
	}

	MV1DeleteModel(meshID);

	// �����̃f�[�^�Ɠ���ւ��Ė������폜
	std::iter_swap(iter, mDuplicatesMesh.end() - 1);
	mDuplicatesMesh.pop_back();
}

//-----------------------------------------------------------------------------
// @brief  �@���ׂẴ��b�V���̉��
// 
// @details duplicate, ���{�̃��f���n���h���A�A�j���[�V�������ׂĂ��J������
// �A�v���P�[�V�����̏I������dxLib_End()���O�ɌĂяo���K�v������B.
//-----------------------------------------------------------------------------
void AssetManager::RemoveAll()
{
	// �S�ẴA�j���[�V�������J������
	for (auto iter = mAnimMap.begin(); iter != mAnimMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	// �S�Ẵ��f�����J������
	for (auto iter = mMeshMap.begin(); iter != mMeshMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	// �S�Ă�Duplicate���폜����
	for (auto iter = mDuplicatesMesh.begin(); iter != mDuplicatesMesh.end(); ++iter)
	{
		MV1DeleteModel(*iter);
	}

	mAnimMap.clear();
	mMeshMap.clear();
	mDuplicatesMesh.clear();
}
