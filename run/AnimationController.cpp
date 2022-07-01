
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
// @param[in] m_modelHandle �A�j���[�V������K�p���郂�f���n���h��.
//-----------------------------------------------------------------------------

AnimationController::AnimationController(int m_modelHandle)
	: m_modelHandle(m_modelHandle)
	, mNowAnimTypeNum(-1)
	, mNowAnimTime(0.0f)
	, mAttachedIndex(0)
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
AnimationController::~AnimationController()
{
}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V�����̒ǉ�.
//-----------------------------------------------------------------------------
int AnimationController::AddAnimation(std::string animFileName, float animFps, bool isLoop)
{
	AnimData anim;
	anim.mAnimFps = animFps;
	anim.mIsLoop = isLoop;

	// �A�j���[�V�����f�[�^�ǂݍ���
	anim.mAnimHandle = ASSET.GetAnimation(animFileName.c_str());
	if (anim.mAnimHandle == -1)
	{
		return -1;
	}
	anim.mAnimIndex = MV1GetAnimNum(anim.mAnimHandle) - 1;

	mAttachedIndex = MV1AttachAnim(m_modelHandle, anim.mAnimIndex, anim.mAnimHandle, TRUE);
	anim.mAnimTotalTime = MV1GetAnimTotalTime(anim.mAnimHandle, anim.mAnimIndex);

	// �A�j���[�V��������
	int test;
	test = MV1DetachAnim(m_modelHandle, mAttachedIndex);

	// �����ɃA�j���[�V�����f�[�^�ǉ�
	mAnimDatas.push_back(anim);

	// vector�ɓ���Y�����ԍ��Ԃ�
	return static_cast<int>(mAnimDatas.size() - 1);
}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V�����̑���������ݒ�.
//-----------------------------------------------------------------------------
void AnimationController::AddAnimTime(float deltaTime)
{
	mNowAnimTime += deltaTime * mAnimDatas[mNowAnimTypeNum].mAnimFps;

	// ���[�v�Đ�
	if (mAnimDatas[mNowAnimTypeNum].mIsLoop && mNowAnimTime > mAnimDatas[mNowAnimTypeNum].mAnimTotalTime)
	{
		mNowAnimTime = 0.0f;
	}
	int test;
	test = MV1SetAttachAnimTime(m_modelHandle, mAttachedIndex, mNowAnimTime);
}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V�����̍Đ����J�n.
//-----------------------------------------------------------------------------
void AnimationController::StartAnimation(int animID)
{
	// �ȑO�̃A�j���[�V�����ƈႤ�A�j���[�V�������������x�f�^�b�`
	if (animID != mNowAnimTypeNum)
	{
		if (mNowAnimTypeNum != -1)
		{
			MV1DetachAnim(m_modelHandle, mAttachedIndex);
		}
		// �V�K�A�j���[�V�������Z�b�g
		mNowAnimTypeNum = animID;
		mAttachedIndex = MV1AttachAnim(m_modelHandle, mAnimDatas[animID].mAnimIndex, mAnimDatas[mNowAnimTypeNum].mAnimHandle, TRUE);
	}
	mNowAnimTime = 0.0f;
	MV1SetAttachAnimTime(m_modelHandle, mAttachedIndex, mNowAnimTime);
}

//-----------------------------------------------------------------------------
// @brief  ���ݎw�肳��Ă���A�j���[�V�����̍Đ����I��.
//-----------------------------------------------------------------------------
void AnimationController::StopAnimation()
{
	mNowAnimTime = mAnimDatas[mNowAnimTypeNum].mAnimTotalTime;
}

//-----------------------------------------------------------------------------
// @brief  ���ݎw�肳��Ă���A�j���[�V�����͍Đ������H.
//-----------------------------------------------------------------------------
bool AnimationController::IsPlaying()
{
	if (!mAnimDatas[mNowAnimTypeNum].mIsLoop && mNowAnimTime > mAnimDatas[mNowAnimTypeNum].mAnimTotalTime)
	{
		//Player::HitFlag();
		return false;
	}
	return true;
}
