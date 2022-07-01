//-----------------------------------------------------------------------------
// @brief  ��Q���F�����Ȃ�.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
ObstructStatic::ObstructStatic(int sourceModelHandle)
	: GameObject(sourceModelHandle)
{
	m_pos = VGet(0, -50, 0);
	hitRadius = 50.0f;
	scale = VGet(0.0f, 0.0f, 0.0f);
}

ObstructStatic::ObstructStatic(int sourceModelHandle, VECTOR _scale)
	: GameObject(sourceModelHandle)
{

	m_pos = VGet(0, -50, 0);
	hitRadius = 30.0f;
	scale = _scale;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
ObstructStatic::~ObstructStatic()
{
	// �����Ȃ�.
}

//-----------------------------------------------------------------------------
// @brief  �X�V.
//-----------------------------------------------------------------------------
void ObstructStatic::Update(float deltaTime)
{

	// �R�c���f���̃X�P�[����13�{�ɂ���
	MV1SetScale(m_modelHandle, scale);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

}
