//-----------------------------------------------------------------------------
// @brief  カメラクラス.
//-----------------------------------------------------------------------------

#define USE_LERP_CAMERA 0

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(100.0f, 4000.0f);

	pos = VGet(0, 0, 0);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	// 処理なし.
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Camera::Update(const Player& player)
{
#if !USE_LERP_CAMERA
	// 真横からプレーヤーをずっと見続ける位置（あとで斜め後ろにしておいてね
	pos = VGet(player.GetPos().x-4000, 200.0f, player.GetPos().z);

#else
	// lerpを使用して実装.
	// lerp(VECTOR a, VECTOR b, float t)は
	// answer = a + ((b-a) * t)
	VECTOR aimPos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f);
	VECTOR posToAim = VSub(aimPos, pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	pos = VAdd(pos, scaledPosToAim);
#endif
	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(pos, player.GetPos());
}