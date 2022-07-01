//-----------------------------------------------------------------------------
// @brief  障害物：動かない.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
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
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
ObstructStatic::~ObstructStatic()
{
	// 処理なし.
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void ObstructStatic::Update(float deltaTime)
{

	// ３Ｄモデルのスケールを13倍にする
	MV1SetScale(m_modelHandle, scale);

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

}
