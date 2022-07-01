//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------

const float Player::COLIDE_DECEL_FAC = 0.4f;			// 障害物にぶつかったときの減速率.

//静的変数の初期化
bool Player::hitFlag = false;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
	: mAnimControl(nullptr)
	,m_hitTime(HIT_TIME+1.0f)
	,m_jumpFlag(false)
	,m_yTemp(0.0f)
	,m_yPrev(0.0f)
	,m_yOrigin(0.0f)
	,m_jumpPower(0.0f)
	,m_gravity(0.4f)
{
	 //３Ｄモデルの読み込み
	m_modelHandle = ASSET.GetMesh("data/model/player/Jammo_LowPoly.mv1");
	MV1SetScale(m_modelHandle, VGet(PLAYER_MODEL_SCALE, PLAYER_MODEL_SCALE, PLAYER_MODEL_SCALE));

	// アニメーションコントローラ
	mAnimControl = new AnimationController(m_modelHandle);

	// アニメーションの読み込み
	mAnimControl->AddAnimation("data/model/player/FastRun.mv1",30.0f,true);
	mAnimControl->AddAnimation("data/model/player/Jump.mv1",30.0f, false);
	mAnimControl->AddAnimation("data/model/player/hit.mv1", 30.0f, false);

	//// 推し
	//m_modelHandle = ASSET.GetMesh("data/model/player/all/allmight.pmx");

	//mAnimControl->AddAnimation("data/model/player/all/allRunning.vmd", 30.0f, true);
	//mAnimControl->AddAnimation("data/model/player/all/allJump.vmd", 30.0f, false);
	//mAnimControl->AddAnimation("data/model/player/all/allRight.vmd", 30.0f, false);

	//MV1SetScale(m_modelHandle, VGet(5.0f, 5.0f, 5.0f));

	mAnimControl->StartAnimation(0);

	tekusutya = LoadGraph("data/model/player/tekusutya.png");
	texIndex = MV1GetMaterialDifMapTexture(m_modelHandle, 0);

	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(m_modelHandle, texIndex, tekusutya, FALSE);

	pos = VGet(0, 5, 500);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Player::~Player()
{
	// モデルのアンロード.
	ASSET.RemoveMesh(m_modelHandle); //MV1DeleteModel(m_modelHandle);

	delete mAnimControl;
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Player::Update(float deltaTime)
{

	//アニメーション処理
	mAnimControl->IsPlaying();
	mAnimControl->AddAnimTime(deltaTime);

	// キー入力取得
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//常にx方向に進む
	pos.x += 5;


	//アニメモーションが再生されていなければ
	if (!mAnimControl->IsPlaying()/*&& m_hitTime >= HIT_TIME*/)
	{
		//走る
		mAnimControl->StartAnimation(0);
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//ジャンプする
		mAnimControl->StartAnimation(1);
	}
	if (hitFlag && !m_hitTime)
	{
		//よろける
		mAnimControl->StartAnimation(2);
	}
	

	//無敵時間カウント
	if (hitFlag)
	{
		m_hitTime += deltaTime * (m_hitTime + 1.0f);
	}

	//無敵時間が終わったらリセットする
	if (m_hitTime >= HIT_TIME)
	{
		m_hitTime = 0.0f;
		ResetHitFlag();
	}


	//---------------------------------------------------------------------------
	// @brief  ジャンプ処理.
	//---------------------------------------------------------------------------
	if (CheckHitKey(KEY_INPUT_SPACE) && !m_jumpFlag)
	{
		m_jumpPower = 10.0f;
		m_jumpFlag = true;
	}
	if (this->pos.y >= 0 && m_jumpFlag)
	{
		m_jumpPower -= m_gravity;
		this->pos.y += m_jumpPower;
	}
	else
	{
		m_jumpFlag = false;
		this->pos.y = 0;
	}


	//3Dモデルの向き設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 270.0f * DX_PI_F / 180.0f, 0.0f));

	//MV1SetAttachAnimTime(m_modelHandle, 0, animTime);

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, pos);

}

//-----------------------------------------------------------------------------
// @brief  描画.
//-----------------------------------------------------------------------------
void Player::Draw()
{
    // ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

}

void Player::OnHitObstruct(GameObject& obstruct)
{
	// 自分自身の位置を障害物のあたり判定分ずらす.
    // Z軸とX軸の二次元座標として位置ずらしを行う.
	VECTOR yZeroPlayer = VGet(pos.x, pos.y, pos.z);
	VECTOR yZeroObstruct = VGet(obstruct.GetPos().x, obstruct.GetPos().y, obstruct.GetPos().z);

	VECTOR obsToPlayer = VSub(yZeroPlayer, yZeroObstruct);

	// ぶつかったときに離す距離。ちょうどだとfloat誤差で重なり続けるので少し間をあける.
	float awayRange = (hitRadius + obstruct.GetHitRadius() + 0.01f);

	VECTOR awayVec = VScale(VNorm(obsToPlayer), awayRange);
	//pos = VAdd(yZeroObstruct, awayVec);
	
	//// ぶつかったら減速する.
	//velocity = VScale(lvelocity, COLIDE_DECEL_FAC);

}

