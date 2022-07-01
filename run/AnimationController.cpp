
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
// @param[in] m_modelHandle アニメーションを適用するモデルハンドル.
//-----------------------------------------------------------------------------

AnimationController::AnimationController(int m_modelHandle)
	: m_modelHandle(m_modelHandle)
	, mNowAnimTypeNum(-1)
	, mNowAnimTime(0.0f)
	, mAttachedIndex(0)
{
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
AnimationController::~AnimationController()
{
}

//-----------------------------------------------------------------------------
// @brief  アニメーションの追加.
//-----------------------------------------------------------------------------
int AnimationController::AddAnimation(std::string animFileName, float animFps, bool isLoop)
{
	AnimData anim;
	anim.mAnimFps = animFps;
	anim.mIsLoop = isLoop;

	// アニメーションデータ読み込み
	anim.mAnimHandle = ASSET.GetAnimation(animFileName.c_str());
	if (anim.mAnimHandle == -1)
	{
		return -1;
	}
	anim.mAnimIndex = MV1GetAnimNum(anim.mAnimHandle) - 1;

	mAttachedIndex = MV1AttachAnim(m_modelHandle, anim.mAnimIndex, anim.mAnimHandle, TRUE);
	anim.mAnimTotalTime = MV1GetAnimTotalTime(anim.mAnimHandle, anim.mAnimIndex);

	// アニメーション解除
	int test;
	test = MV1DetachAnim(m_modelHandle, mAttachedIndex);

	// 末尾にアニメーションデータ追加
	mAnimDatas.push_back(anim);

	// vectorに入る添え字番号返す
	return static_cast<int>(mAnimDatas.size() - 1);
}

//-----------------------------------------------------------------------------
// @brief  アニメーションの増分時刻を設定.
//-----------------------------------------------------------------------------
void AnimationController::AddAnimTime(float deltaTime)
{
	mNowAnimTime += deltaTime * mAnimDatas[mNowAnimTypeNum].mAnimFps;

	// ループ再生
	if (mAnimDatas[mNowAnimTypeNum].mIsLoop && mNowAnimTime > mAnimDatas[mNowAnimTypeNum].mAnimTotalTime)
	{
		mNowAnimTime = 0.0f;
	}
	int test;
	test = MV1SetAttachAnimTime(m_modelHandle, mAttachedIndex, mNowAnimTime);
}

//-----------------------------------------------------------------------------
// @brief  アニメーションの再生を開始.
//-----------------------------------------------------------------------------
void AnimationController::StartAnimation(int animID)
{
	// 以前のアニメーションと違うアニメーションがきたら一度デタッチ
	if (animID != mNowAnimTypeNum)
	{
		if (mNowAnimTypeNum != -1)
		{
			MV1DetachAnim(m_modelHandle, mAttachedIndex);
		}
		// 新規アニメーションをセット
		mNowAnimTypeNum = animID;
		mAttachedIndex = MV1AttachAnim(m_modelHandle, mAnimDatas[animID].mAnimIndex, mAnimDatas[mNowAnimTypeNum].mAnimHandle, TRUE);
	}
	mNowAnimTime = 0.0f;
	MV1SetAttachAnimTime(m_modelHandle, mAttachedIndex, mNowAnimTime);
}

//-----------------------------------------------------------------------------
// @brief  現在指定されているアニメーションの再生を終了.
//-----------------------------------------------------------------------------
void AnimationController::StopAnimation()
{
	mNowAnimTime = mAnimDatas[mNowAnimTypeNum].mAnimTotalTime;
}

//-----------------------------------------------------------------------------
// @brief  現在指定されているアニメーションは再生中か？.
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
