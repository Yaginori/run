//-----------------------------------------------------------------------------
// @brief  �J�����N���X.
//-----------------------------------------------------------------------------

#define USE_LERP_CAMERA 0

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(100.0f, 4000.0f);

	pos = VGet(0, 0, 0);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	// �����Ȃ�.
}

//-----------------------------------------------------------------------------
// @brief  �X�V.
//-----------------------------------------------------------------------------
void Camera::Update(const Player& player)
{
#if !USE_LERP_CAMERA
	// �^������v���[���[�������ƌ�������ʒu�i���ƂŎ΂ߌ��ɂ��Ă����Ă�
	pos = VGet(player.GetPos().x-4000, 200.0f, player.GetPos().z);

#else
	// lerp���g�p���Ď���.
	// lerp(VECTOR a, VECTOR b, float t)��
	// answer = a + ((b-a) * t)
	VECTOR aimPos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f);
	VECTOR posToAim = VSub(aimPos, pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	pos = VAdd(pos, scaledPosToAim);
#endif
	// �J�����Ɉʒu�𔽉f.
	SetCameraPositionAndTarget_UpVecY(pos, player.GetPos());
}